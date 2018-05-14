//
//  EmergencyRoom.cpp
//  E.R-Simulator
//
//  Created by Esrey on 5/6/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//  separate cpp file that is built into the project directly, runs when run the program
//  #ifdefdebug so unit testing will only be run under such instead of under the entire program running 

#include "EmergencyRoom.hpp"
#include <sstream>

bool EmergencyRoom::medicsFree()
{
    int test = 0; //if a doctor is busy, increment test
    for ( unsigned i = 0; i < Medics.size(); i++)
    {
        if (Medics[i]->isBusy()) {
            test++;
        }
    }
    if (test == Medics.size()) //return false if all are occupied
        return false;
    else
        return true; //returns a doctor that is not busy
};

bool EmergencyRoom::doctorsFree()
{
    int test = 0; //busy doctors
    int dr_Count = 0; //total number of doctors that the E.R. has working
    for ( unsigned i = 0; i < Medics.size; i++)
    {
        if ( typeid(*(Medics[i])) == typeid(Doctor)) {
            dr_Count++;
            if (Medics[i]->isBusy()){
                test++;
            }
        
        }
    }
    if (test == dr_Count)
        return false;
    else
        return true; //free doctor available
    
};
//Updates and checks to identify anyone that has completed their patient treatment
//if they are done, then update the records and keep track of such information
//Assigns 10-20 priority to any free doctors
//assigns 1-10 to any free nurses (medics)
void EmergencyRoom::updateDoctors()
{
    for (unsigned i = 0; i < Medics.size(); i++)
    {
        if (Medics[i]->isBusy())
        {
            std::pair<bool, Patient> test = Medics[i]->update(clock); //update function
            if (test.first){
                Patient departing = test.second;
                numTreated++;
                totalWait=+ departing.getVisitTime();
                Record[departing.getName()].push_back(departing.getPriority()); //add the information to the record to be searched afterwards if need be
            }
                
            }
        }
    //patients with priority over 10 (Doctor treatment status)
    while (medicsFree() && (!patientsOver10.empty() || !patientsUnder10.empty())) //free medic available and patients are waiting in their respective queues
    {
        for (unsigned i = 0; i < Medics.size(); i++)
        {
            if (typeid(Doctor) ==typeid(*Medics[i])) && !Medics[i] ->isBusy())
            {
                Medics[i]->treatPatient (patientsOver10.top()); //doctor needs to provide treatment
                patientsOver10.pop();
                break;
            }
        }
        
    }
    //patients with priority under 10(Nurse treatment status)
    if (!medicsFree() || patientsUnder10.empty()){
        break;
    }
    
    for (unsigned i = 0; i < Medics.size(); i++)
    {
        if (!Medics[i]->isBusy()){
            Medics[i]->treatPatient(patientsUnder10.top()); //any medic can provide treatment, doctors are available if there are no patients over 10 waiting in the queue for over a priority of 10.
            patientsUnder10.pop();
            break;
        }
    }
        
}

EmergencyRoom::EmergencyRoom(int numDoctors, int numNurses, int arrivalRate) : arrivalRate(arrivalRate), numTreated(0), totalwait(0), clock(0)
{
    buildDatabase(names); //fills the names vector with all the names in the file
    
    //nurses take patients that have 1-10 over doctors for efficiency
    for (int i = 0; i < numNurses; i++) {
        Medics.push_back(new Nurse());
    }
    
    for (int i = 0; i < numDocs; i++) {
        Medics.push_back(new Doctor());
    }
    
}

void EmergencyRoom::update() //add a new patient according to the rate that the user initially input
{
    clock++; //update
    
    if (needNewPatient(arrivalRate)) {
        
        //new patient
        Patient newPatient(clock, names);
        //add new patient to the correct priority queue according to their level of illness
        if (newPatient.getPriority() > 10) { //greater than 10 priority
            patientsOver10.push(newPatient);
        }
        else {
            patientsUnder10.push(newPatient); //less than 10 priority
        }
        Patient->visitCount++; //increments visit count for that particular patient
        
        
    }
    //update the doctors queue
    updateDoctors();
    
}

void EmergencyRoom::listNames() //list the names of those in the emergency room
{
    //iterates through record, keys are the output (names) to the map in Emergency room , technique modeled after map lab in class
    std::map<std::string, std::list<int>>::iterator it = Record.begin();
    int i = 0;
    for (;it != Record.end(); i++, ++it) {
        std::cout << it->first << ", ";
        if (i % 10 == 0 && i != 0)
            std::cout << std::endl;
    }
    
    
}
std::string EmergencyRoom::getRecord(std::string name)
{
    std::map<std::string, std::list<int>>::iterator it = Record.find(name);
    
    //if no name found
    if (it == Record.end())
        return std::string("No records were found under that name\n");
    
    //if name found
    else {
        
    
        std::stringstream ss;
        ss << "Name: " << it->first << "\n";
        std::list<int> illnesses = it->second;
        ss << "Illness severities: ";
        int illnesscount = 0;
        
        for (std::list<int>::iterator it = illnesses.begin(); it != illnesses.end();) {
            ss << *it;
            illnesscount++;
            if (++it != illnesses.end())
                ss << ", ";
        }
        ss << "\n" << "Total number of illnesses from this individual: " << illnesscount << "\n";
        return ss.str();
        //waiting time for the individual in the e.r room
        
    }
    
    
} 
}
