#include<iostream>
#include"calc.h"
#include"nsolver.h"

int main(){

  //TODO: SolveBT only works with signs placed ones
  //TODO: Also it needs major refactoring!
  std::cout << "Solution to 24, {1, 5, 5 ,5}: " << nsolver::BruteForce(24, {1,5,5,5}) << std::endl;
  std::cout << "Solution to 24, {1, 3, 4 ,6}: " << nsolver::BruteForce(24, {1,3,4,6}) << std::endl;

 return 0; 
}
