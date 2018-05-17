//
//  Physician.cpp
//  CS273 Final
//
//  Created by Esrey on 5/15/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//

#include "Physician.hpp"

std::pair<bool, Patient> Physician::update(long long int clock) //Returns true if the patient is finished treating, and then the returned patient is used to create a record
//If the patient still isn't done being treated, false is returned with a default patient object
{
    if (clock - currentTreatmentTime >= currentPatient.getArrivalTime()) { //if we are done treating current patient
        
        //update the physician and doctor's data to be done with treatment
        currentPatient.setDepartureTime(clock);
        currentTreatmentTime = 0;
        return std::make_pair(true, currentPatient);
    }
    else //return false, and that we are not done
        return std::make_pair(false, Patient());
}

bool Physician::isBusy() //returns true if they have a patient
{
    if (currentTreatmentTime > 0) //This was the easiest way I found to check for being busy.
        //Potentially pointers could have been used to store the patient, with a NULL ptr check done here to check
        //to see if the doctor has a patient. But it wasn't working and this seemed simple enough.
        return true;
    else
        return false;
}

//generates visit time for the current patient 1-20 min for docs
void Doctor::treatPatient(Patient newPatient)
{
    currentPatient = newPatient;
    currentTreatmentTime = 1 + rand() % 20;
}

//generates visit time for the current patient 1-10 min for nurses
void Nurse::treatPatient(Patient newPatient)
{
    currentPatient = newPatient;
    currentTreatmentTime = 1 + rand() % 10;
}
