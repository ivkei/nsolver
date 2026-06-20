#include<string>
#include<vector>

namespace nsolver{

//Solve an n-game (e.g. 24-game) using vector of numbers v and return string to show answer
//Uses 4 basic operations
//Return "" if nothing was found
std::string BruteForce(int n, std::vector<int> v);

}
