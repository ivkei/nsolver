#include<iostream>
#include"calc.h"
#include"nsolver.h"
#include<sstream>

//TODO: non-brute force approaches?
//TODO: optimize bruteforce?
//TODO: 3, 3, 8, 8 doesnt work

template<class T>
T Prompt(std::string);

template<>
std::string Prompt<std::string>(std::string message){
  std::string input;

  std::cout << message;
  std::getline(std::cin, input);

  return input;
}

template<>
int Prompt<int>(std::string message){
  std::string input = Prompt<std::string>(message);
  return std::stoi(input);
}

template<>
std::vector<int> Prompt<std::vector<int>>(std::string message){
  std::string input = Prompt<std::string>(message);
  std::vector<int> res;
  int i;

  std::stringstream ss{input};
  while (ss >> i){
    res.push_back(i);
  }
  
  return res;
}

int main(){
  int n = Prompt<int>("Enter the target number (e.g. 24): ");
  std::vector<int> vals = Prompt<std::vector<int>>("Enter construction values (e.g. 1 5 5 5): ");

  //Output what parsed
  std::cout << "Your target number is " << n << std::endl;
  std::cout << "Your construction values are { ";
  for (int i : vals){
    std::cout << i << " ";
  }
  std::cout << "}" << std::endl;

  std::cout << "Started!" << std::endl;

  std::string res = nsolver::BruteForce(n, vals, 2);

  if (res == ""){
    std::cout << "No solution was found" << std::endl;
    return 1;
  }
  std::cout << n << " = " << res << std::endl;

  //Examples/Test cases
  //std::cout << "Solution to 24, {1, 5, 5 ,5}: " << nsolver::BruteForce(24, {1,5,5,5}) << std::endl;
  //std::cout << "Solution to 24, {1, 3, 4 ,6}: " << nsolver::BruteForce(24, {1,3,4,6}) << std::endl;

 return 0; 
}
