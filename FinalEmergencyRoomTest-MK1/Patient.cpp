//
//  Patient.cpp
//  CS273 Final
//
//  Created by Esrey on 5/15/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//

#include "Patient.hpp"

bool Patient::operator<(const Patient Other) const //compares illness priority, followed by arrival time if the two priorities are equal
//used to sort people in the priority queues they are stored in
{
    if (!(this->illnessPriority == Other.illnessPriority)) //if they don't have the same priority, procees as normal
        return this->illnessPriority < Other.illnessPriority;
    else //if they do have the same priority, go with the person who arrived first
        return this->arrivalTime < Other.arrivalTime;
}
