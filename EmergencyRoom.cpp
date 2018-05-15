//
//  EmergencyRoom.cpp
//  CS273 Final
//
//  Created by Esrey on 5/15/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//

#include "EmergencyRoom.hpp"
#include <sstream>

// a medic can be a doctor or a nurse for this program

bool EmergencyRoom::medicsFree() //if all the medics are busy
{
    int test = 0; //counts the number of doctors that are occupied with patients
    for (unsigned i = 0; i < Medics.size(); i++) {
        if (Medics[i]->isBusy()) {
            test++;
        }
    }
    if (test == Medics.size()) //if all the doctors are busy
        return false;
    else
        return true; //else a doctor is free and can treat a patient from 1-20
}

bool EmergencyRoom::docsFree() //all the doctors are busy
{
    int test = 0; //counts the number of doctors
    int docCount = 0; //counts the number of doctors
    for (unsigned i = 0; i < Medics.size(); i++) {
        if (typeid(*(Medics[i])) == typeid(Doctor)) {
            docCount++;
            if (Medics[i]->isBusy()) {
                test++;
            }
        }
    }
    
    if (test == docCount) //if all the doctors are busy
        return false; //return false
    else
        return true; //otherwise there is a free doctor so return true
}

//Updates and checks to identify anyone that has completed their patient treatment
//if they are done, then update the records and keep track of such information
//Assigns 10-20 priority to any free doctors
//assigns 1-10 to any free nurses (medics)
void EmergencyRoom::updateDoctors()
{
    for (unsigned i = 0; i < Medics.size(); i++) { //for all the doctors
        
        if (Medics[i]->isBusy()) { //doctors treating a patient
            
            std::pair<bool, Patient> check = Medics[i]->update(clock); //update the emergency room
            
            if (check.first) { //if the doctor is finished treating their patient
                
                //Update patient's records
                Patient departing = check.second;
                numTreated++;
                totalWait += departing.getVisitTime(); //total patient's wait time
                Record[departing.getName()].push_back(departing.getPriority());//add the information to the record to be searched afterwards if need be
            }
        }
    }
    //patients with priority over 10 (Doctor treatment status)
    while (medicsFree() && (!patientsOver10.empty() || !patientsUnder10.empty()))
    {
        
        //free medic available and patients are waiting in their respective queues
        while (!patientsOver10.empty() && docsFree()) {
            
            for (unsigned i = 0; i < Medics.size(); i++) { //searching through the Medics
                if (typeid(Doctor) == typeid((*Medics[i])) && !Medics[i]->isBusy()) { //if we found a doctor that isn't busy
                    
                    //treat the new patient with that doctor
                    Medics[i]->treatPatient(patientsOver10.top());//doctor needs to provide treatment
                    patientsOver10.pop();
                    break;
                }
            }
            
        }
        //patients with priority under 10(Nurse treatment status)
            if (!medicsFree() || patientsUnder10.empty())
            break;
        
        
        for (unsigned i = 0; i < Medics.size(); i++) {
            
            //if a medic is free
            if (!Medics[i]->isBusy()) {
                Medics[i]->treatPatient(patientsUnder10.top());//any medic can provide treatment, doctors are available if there are no patients over 10 waiting in the queue for over a priority of 10.
                patientsUnder10.pop();
                break;
            }
        }
    }
}

EmergencyRoom::EmergencyRoom(int numDocs, int numNurses, int arrivalRate) : arrivalRate(arrivalRate), numTreated(0), totalWait(0), clock(0)
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
            patientsUnder10.push(newPatient);
        }
        
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

std::string EmergencyRoom::getRecord(std::string name)  //Record Search
{
    std::map<std::string, std::list<int>>::iterator it = Record.find(name);
    
    if (it == Record.end()) //if no name in record
        return std::string("No records were found under that name\n");
    
    else { //if name is in record.
        
        
        std::stringstream ss;
        ss << "Name: " << it->first << "\n";
        std::list<int> illnesses = it->second;
        ss << "Illness severities: ";
        int illnesscount = 0; //number of illnesses
        
        for (std::list<int>::iterator it = illnesses.begin(); it != illnesses.end();) {
            ss << *it;
            illnesscount++;
            if (++it != illnesses.end())
                ss << ", ";
        }
        ss << "\n" << "Total number of illnesses: " << illnesscount << "\n";
        return ss.str();
    }
}
