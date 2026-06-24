#pragma once

#include<string>
#include<vector>

namespace nsolver{

//Solve an n-game (e.g. 24-game) using vector of numbers v and return string to show answer
//Uses 4 basic operations
//Return "" if nothing was found
//Precision determines the amount of pairs of parenthesis placed in, dont set it higher than 2 for the sake of you own computer (My 16GBs of RAM ran out :( when I tried)
//The more the better
//Make it a one for adequate precision and speed
//T takes float or int
template<class T>
std::string BruteForce(T n, std::vector<T> v, int precision = 2);

//Does the same as brute force but faster (hopefully...)
template<class T>
std::string FastBruteForce(T n, std::vector<T> v);

}
