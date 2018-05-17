//
//  Physician.hpp
//  CS273 Final
//
//  Created by Esrey on 5/15/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//

#ifndef Physician_hpp
#define Physician_hpp
#include "Patient.hpp"
#include <utility>

class Physician {
protected:
    Patient currentPatient; //used to store the current patient they are treating
    //maybe this should be a pointer?? This seems to work fine though
    int currentTreatmentTime; //used to store the current time that the physician is recquired to treat the patient for
public:
    Physician() : currentPatient(), currentTreatmentTime(0) {}; //Default constructor to be used by derived classes
    virtual void treatPatient(Patient newPatient) = 0;
    std::pair<bool, Patient> update(long long int clock); //Returns true if the patient is finished treating, and then the returned patient is used to create a record
    //If the patient still isn't done being treated, false is returned with a default patient object
    bool isBusy(); //returns true if they have a patient
};

class Doctor : public Physician {
public:
    Doctor() : Physician() {}; //Default constructor
    void treatPatient(Patient newPatient); //Used to add a new patient to be treated
};

class Nurse : public Physician {
public:
    Nurse() : Physician() {}; //Default constructor
    void treatPatient(Patient newPatient); //Used to add a new patient to be treated
};

#endif
