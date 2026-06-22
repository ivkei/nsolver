#include<string>
#include<vector>

namespace nsolver{

//Solve an n-game (e.g. 24-game) using vector of numbers v and return string to show answer
//Uses 4 basic operations
//Return "" if nothing was found
//Precision determines the amount of pairs of parenthesis placed in, dont set it higher than 2 for the sake of you own computer (My 16GBs of RAM ran out :( when I tried)
//The more the better
//Make it a one for adequate precision and speed
std::string BruteForce(int n, std::vector<int> v, int precision = 2);

}
