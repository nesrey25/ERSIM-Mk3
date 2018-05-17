//
//  main.cpp
//  CS273 Final
//
//  Created by Esrey on 5/15/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//

#include <iostream>
#include "EmergencyRoom.hpp"
#include "Menu.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include "UnitTest.cpp"

using namespace std;

int main() {
    
    //runTests(); (how we would run the unit tests)
    
    cout << "Welcome to the Emergency Room simulator!\n\n";
    string prompt = "What would you like the arrival rate of patients to be (patients/hr): ";
    int rate = read_int(prompt, 1, 60);
    prompt = "How many doctors would you like there to be (1-20): ";
    int docs = read_int(prompt, 1, 20);
    prompt = "How many nurses would you like there to be (1-20): ";
    int nurses = read_int(prompt, 1, 20);
    
    EmergencyRoom theRoom(docs, nurses, rate); //create the emergency room based on the user's input
    
    long long int FINISHTIME = 7 * 24 * 60; //simulating for one week
    
    while (theRoom.getTime() < FINISHTIME) { //run the simulation until the time is up
        theRoom.update();
    }
    
    double averageWait = theRoom.getTotalWait() / theRoom.getNumTreated();
    
    cout << "The average visit time for each patient was " << averageWait << " minutes.\n\n";
    
    
    
    while (true) {
        string    menu_string = "Would you like to: \n";
        menu_string += "   0 - See the list of patient names\n";
        menu_string += "   1 - Search for the details of a patient by name\n";
        menu_string += "   2 - Exit\n";
        menu_string += "Enter: ";
        
        cout << menu_string;
        
        string choice = "";
        cin >> choice;
        
        
        if (choice[0] == '2')
            //EXIT
            break;
        else if (choice[0] == '0')
            //List all the names
            theRoom.listNames();
        else {
            //Search the Record for a particular name
            string firstName;
            string lastName;
            string name;
            
            cout << "What name would you like to search for? " <<endl;
            cout << "Please enter their first name: " << endl;
            cin >> firstName;
            
            cout << "Please enter their last name: " << endl;
            cin >> lastName;
            
            for(int i = 0; i < firstName.length(); i++)
            {
                firstName[i] = toupper(firstName[i]);
            }
            
            for(int i = 0; i < lastName.length(); i++)
            {
                lastName[i] = toupper(lastName[i]);
            }
            
            name = firstName + " " + lastName;
            cout << theRoom.getRecord(name);
        }
    }
    
    return 0;
}

