#include<string>
#include<iostream>

namespace nsolver{

template<class...TArgs>
void LogToConsole(const std::string& preinfo, const std::string& color, TArgs&&...args){
    std::cout << color << preinfo << " ";
    ((std::cout << std::forward<TArgs>(args)), ...);
    std::cout << "\033[0m" << std::endl;
  }

#ifndef NSOLVER_DISABLE_LOGGER
  #define LOG_ERROR(...) LogToConsole("[ERROR] (nsolver)", "\033[31m", __VA_ARGS__)
  #define LOG_INFO(...) LogToConsole("[INFO] (nsolver)", "\033[32m", __VA_ARGS__)
  #define LOG_WARNING(...) LogToConsole("[WARNING] (nsolver)", "\033[33m", __VA_ARGS__)
#endif

}
