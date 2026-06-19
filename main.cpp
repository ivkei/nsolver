//TODO: github
#include<iostream>
#include"calc.h"
#include"nsolver.h"

int main(){

  std::string find;
  std::cout << "Enter expression: ";
  std::cin >> find;
  std::cout << find << " = " << calc::Calculate(find) << std::endl;

 return 0; 
}
