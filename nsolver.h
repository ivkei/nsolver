#pragma once

#include<string>
#include<vector>

namespace nsolver{

//Solve an n-game (e.g. 24-game) using vector of numbers v and return string as an answer
//Uses 4 basic operations
//Return "" if nothing was found
//T takes float or int
template<class T>
std::string BruteForce(T n, std::vector<T> v);

}
