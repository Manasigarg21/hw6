#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib> 

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				HASH_INDEX_T w[5] = {};
				HASH_INDEX_T temp[30] = {};
				int i = 0;
				for (auto iterator = k.rbegin(); iterator != k.rend(); ++iterator){
					temp[i] = letterDigitToNumber(*iterator); 
					i++;  
				}

				for (int i =0; i<30; i+=6){
					HASH_INDEX_T power = 1; 
					for (int j = 0; j<6; j++){
						w[4 - i / 6] += ((temp[i+j]) *power );
						power *= 36;
					}
				}

				return (rValues[0]* w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4]*w[4]);

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        letter = std::tolower(letter);
        // Add code here or delete this helper function if you do not want it
				if (letter >= 'a' && letter <= 'z'){
					return letter - 'a';  
				}
				else{
					return (letter - '0') + 26ull; 
				}
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
