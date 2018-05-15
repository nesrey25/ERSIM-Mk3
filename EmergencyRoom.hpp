//
//  EmergencyRoom.hpp
//  CS273 Final
//
//  Created by Esrey on 5/15/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//

#ifndef EmergencyRoom_hpp
#define EmergencyRoom_hpp

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include "Patient.hpp"
#include "Physician.hpp"
#include "RandomGenerator.hpp"

class EmergencyRoom {
private:
    int arrivalRate; //arrival rate in terms of patients per hour
    long long int clock; //used to keep track of how long the sim has been running for
   
    double numTreated;  //number of patients successfully treated
    double totalWait; //used with numTreated to find average wait time
    std::vector<std::string> names; //used in producing a random name
    
    std::priority_queue<Patient> patientsOver10; //used to keep track of the patients with a priority of over 10
    std::priority_queue<Patient> patientsUnder10; //used to keep track of the patients with a priority of below 10
    
    
    std::vector<Physician *> Medics; //A vector to hold all of the Physicians in the emergency room
    std::map<std::string, std::list<int>> Record; //Used to store the records of all the patients that have been treated
    
    bool medicsFree(); //if all the medics are busy returns false
    bool docsFree(); //if all the doctors are busy returns false
    void updateDoctors(); //update of medics
    
public:
    double getNumTreated() { return numTreated; }
    double getTotalWait() { return totalWait; }
    EmergencyRoom(int numDocs, int numNurses, int arrivalRate);
    void update(); //Adds a new patient if necessary, and then calls updateDoctors()
    long long int getTime() { return clock; }
    void listNames(); //displays all the names of the people in the Record
    std::string getRecord(std::string name); //searched the Record for a person by name and returns a nicely formatted string of their record
};

#endif /* EmergencyRoom_hpp */
