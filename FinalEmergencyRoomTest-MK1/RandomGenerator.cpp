//
//  RandomGenerator.cpp
//  CS273 Final
//
//  Created by Esrey on 5/15/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//

#include "RandomGenerator.hpp"

#include <time.h>
#include <fstream>
#include <iostream>

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void buildDatabase(std::vector<std::string>& names) //gets all the names from the text file and stores them to the vector
{
    srand(time(NULL));
    std::ifstream surnames;
    std::ifstream firstNames;
    
    firstNames.open("/Users/Kelly/Desktop/residents_of_273ville.txt");
    surnames.open("/Users/Kelly/Desktop/surnames_of_273ville.txt");
    
    //executes if both files open, and pairs up first and last names by concatenating them into one string after making both into all caps for easy string comparison
    if (surnames && firstNames) {
        std::string lastName;
        std::string firstName;
        while (getline(surnames, lastName) && getline(firstNames, firstName)) {
            rtrim(firstName);
            rtrim(lastName);
            
            for(int i = 0; i < firstName.length(); i++)
            {
                firstName[i] = toupper(firstName[i]);
            }
            
            std::string name;
            name = firstName + " " + lastName;
            names.push_back(name);
        }
    }
    else {
        //This could be better in terms of exception handling...
        names.push_back("Default Patient Name - Error reading from file");
        std::cout << "Failed to open the file\n";
    }
    surnames.close();
    firstNames.close();
}

int randomPriority() //generates a random illness priority using the probabilities defined in the outline
//being 70% to be 1-10, 20% to be 11-15, 10% to be 15-20
{
    int x = rand() % 10;
    if (x <= 6)
        return rand() % 10;
    else if (x <= 8)
        return 11 + rand() % 5;
    else
        return 16 + rand() % 5;
}

std::string randomSurname(std::vector<std::string>& names) //picks a random name from the list
{
    int i = rand() % names.size();
    return names[i];
}

bool needNewPatient(int ratePerHour) //Uses the inputted rate to randomly decide if a new patient needs to be generated
{
    int ranNum = rand() % 60;
    if (ranNum < ratePerHour)
        return true;
    else
        return false;
}
