//
//  UnitTest.cpp
//  FinalEmergencyRoomTest-MK1
//
//  Created by Kelly Olivier on 5/15/18.
//  Copyright © 2018 Kelly Olivier. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "EmergencyRoom.hpp"
#include "Patient.hpp"
#include "Physician.hpp"
#include "RandomGenerator.hpp"

/*
 
 Could not make unit tests for code due to the way the project was constructed, but to make up for this we have exception testing built into the code as well as catch and throw statements to ensure correct input and make a program that runs more smoothly.
 
 When we did try to make the unit test seen below there were immediately linker errors which prevented the whole project from running. 
 
 using namespace std;

bool testPhysician()
{
    bool overallWorks = false;
    
    Doctor * doc = new Doctor();
    Nurse * nur = new Nurse();
    
    if (doc && nur)
    {
        overallWorks = true;
    }
    
    return overallWorks;
}

void runTests()
{
    Patient * patient = new Patient();
    
    
    bool physicianTest = testPhysician();
 
    vector <string> testNames;
    testNames.push_back("NANCY");
    testNames.push_back("DREW");
    testNames.push_back("KELLY");
    testNames.push_back("NATE");
 
    
    cout << "Physician is working according to unit tests: " << physicianTest << endl;
}
*/
