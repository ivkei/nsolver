#include<iostream>
#include<sstream>

#include"nsolver.h"

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
float Prompt<float>(std::string message){
  std::string input = Prompt<std::string>(message);
  return std::stold(input);
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

template<>
std::vector<float> Prompt<std::vector<float>>(std::string message){
  std::string input = Prompt<std::string>(message);
  std::vector<float> res;
  float i;

  std::stringstream ss{input};
  while (ss >> i){
    res.push_back(i);
  }
  
  return res;
}

int main(){
  auto n = Prompt<int>("Enter the target number (e.g. 24): ");
  auto vals = Prompt<std::vector<int>>("Enter construction values (e.g. 1 5 5 5): ");

  //Output what parsed
  std::cout << "Your target number is " << n << std::endl;
  std::cout << "Your construction values are { ";
  for (auto i : vals){
    std::cout << i << " ";
  }
  std::cout << "}" << std::endl;

  std::string res = nsolver::BruteForce<int>(n, vals);

  if (res == ""){
    std::cout << "No solution was found" << std::endl;
    return 1;
  }
  std::cout << n << " = " << res << std::endl;

  //Examples/Test cases
  //std::cout << "Solution to 24, {1, 5, 5 ,5}: " << nsolver::BruteForce<int>(24, {1,5,5,5}) << std::endl;
  //std::cout << "Solution to 24, {1, 3, 4 ,6}: " << nsolver::BruteForce<int>(24, {1,3,4,6}) << std::endl;
  //std::cout << "Solution to 0.75, {1.5, 0.5, 8, 7}: " << nsolver::BruteForce<float>(0.75f, {0.5f, 1.5f, 7.0f, 8.0f}) << std::endl;

 return 0; 
}
