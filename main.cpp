#include<iostream>
#include"calc.h"
#include"nsolver.h"
#include<sstream>

//TODO: write main better
//TODO: write readme
//TODO: test cases with 5 numbers
//TODO: 10, {5, 2} doesnt work

int main(){
  //Target n
  std::string strN;
  std::cout << "Enter the target number (e.g. 24): ";
  std::getline(std::cin, strN);
  int n = std::stoi(strN);

  //Construction numbers
  std::string strVals;
  std::cout << "Enter construction values (e.g. 1, 5, 5, 5), please arrange them to have a space in between of them: #1 #2 ..." << std::endl;
  std::getline(std::cin, strVals);
  std::vector<int> intVals;

  std::stringstream ss(strVals);
  int m;
  while (ss >> m){
    intVals.push_back(m);
  }

  //Output what parsed
  std::cout << "Your target number is " << n << std::endl;
  std::cout << "Your construction values are { ";
  for (int i : intVals){
    std::cout << i << " ";
  }
  std::cout << "}" << std::endl;

  std::cout << "Started!" << std::endl;

  std::string res = nsolver::BruteForce(n, intVals);

  if (res == ""){
    std::cout << "No solution was found" << std::endl;
    return 1;
  }
  std::cout << n << " = " << res << std::endl;

  //std::cout << "Solution to 24, {1, 5, 5 ,5}: " << nsolver::BruteForce(24, {1,5,5,5}) << std::endl;
  //std::cout << "Solution to 24, {1, 3, 4 ,6}: " << nsolver::BruteForce(24, {1,3,4,6}) << std::endl;

 return 0; 
}
