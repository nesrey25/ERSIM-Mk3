//
//  Patient.hpp
//  E.R-Simulator
//
//  Created by Esrey on 5/6/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//

#ifndef Patient_hpp
#define Patient_hpp

#include <stdio.h>
#include "RandomGenerator.hpp"
#include <string>

class Patient {
private:
    std::string name; //stores their last name in UPPER CASE
    long long int arrivalTime; //stores the time at which they arrive at the hospital
    int illnessPriority; //number from 1 - 20 that determines the patients illness priority
    long long int departureTime; //stores the time at which they departed from the hospital
public:
    Patient() : name(""), arrivalTime(0), illnessPriority(0), departureTime(0) {};
    Patient(long long int time, std::vector<std::string> names) : name(randomSurname(names)), illnessPriority(randomPriority()),
    arrivalTime(time) {}; //constructor uses the functions from RandomGenerator to get the name and illness priority
    std::string getName() { return name; }
    int getPriority() { return illnessPriority; }
    bool operator<(const Patient Other) const; //compares illness priority and arrival time to throw into appropriate queue
    //used to sort people in the priority queues
    long long int getArrivalTime() { return arrivalTime; }
    long long int getVisitTime() { return departureTime - arrivalTime; }
    void setDepartureTime(long long int time) { departureTime = time; }
};

#endif /* Patient_hpp */
