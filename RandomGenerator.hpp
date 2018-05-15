//
//  RandomGenerator.hpp
//  CS273 Final
//
//  Created by Esrey on 5/15/18.
//  Copyright © 2018 Esrey Enterprises. All rights reserved.
//

#ifndef RandomGenerator_hpp
#define RandomGenerator_hpp

#include <string>
#include <vector>

void buildDatabase(std::vector<std::string> &names); //gets all the names from the text file and stores them to the vector
int randomPriority(); //generates a random illness priority using the probabilities defined in the outline
//being 70% to be 1-10, 20% to be 11-15, 10% to be 15-20
std::string randomSurname(std::vector<std::string> &names); //picks a random name from the list
bool needNewPatient(int ratePerHour); //Uses the inputted rate to randomly decide if a new patient needs to be generated

#endif /* RandomGenerator_hpp */
