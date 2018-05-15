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

void buildDatabase(std::vector<std::string>& names) //gets all the names the text file and stores them to the vector
{
    srand(time(NULL));
    std::ifstream surnames;
    surnames.open("/Users/Esrey/Desktop/residents_of_273ville.txt"); //text file that reads in names of patients 
    if (surnames) {
        std::string name;
        while (getline(surnames, name)) {
            names.push_back(name);
        }
        surnames.close();
    }
    else {
        names.push_back("Default Patient Name - Error reading from file");
        std::cout << "Failed to open the file\n";
    }
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

bool needNewPatient(int ratePerHour) //A new patient needs to be generated if randomly needed based upon rate 
{
    int ranNum = rand() % 60;
    if (ranNum < ratePerHour)
        return true;
    else
        return false;
}
