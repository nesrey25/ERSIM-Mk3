//
//  RandomGenerator.hpp
//  E.R-Simulator
//
//  Created by Esrey on 5/6/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//

#ifndef RandomGenerator_hpp
#define RandomGenerator_hpp

#include <stdio.h>
#include <string>
#include <vector>

void buildDatabase(std::vector<std::string> &names); //retrieves all text file names and inputs into random generator vector for simulation to run

int randomPriority(); //generates a random illness priority using the probabilities of the likelihood of a certain injury occurring
//being 70% to be 1-10, 20% to be 11-15, 10% to be 15-20

std::string randomSurname(std::vector<std::string> &names); //picks a random name from cs273ville file

bool needNewPatient(int ratePerHour); //Uses the inputted rate to randomly choose new patient from the list


#endif /* RandomGenerator_hpp */
