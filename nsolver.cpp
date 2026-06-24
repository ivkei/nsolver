#include"nsolver.h"

#include"calc.h"

#include<string>

#define EPSILON 10e-5

template<class T>
static T Abs(T f){
  if (f > 0) return f;
  else return -f;
}

//Neither did I want this, trust
//Does epsilon equal for floats
template<class T, class U>
static bool Eq(T v1, U v2){
  return v1 == v2;
}

template<>
bool Eq<float, float>(float v1, float v2){
  return Abs<float>(v1 - v2) < EPSILON;
}

template<>
bool Eq<float, int>(float v1, int v2){
  return Abs<float>(v1 - static_cast<float>(v2)) < EPSILON;
}

template<>
bool Eq<int, float>(int v1, float v2){
  return Abs<float>(static_cast<float>(v1) - v2) < EPSILON;
}

template<class T>
static bool BruteForceBacktrack(T n, std::vector<std::string>& pool);

//For brute force backtrack, a helper
#define PERFORM(op)\
  pool.insert(pool.begin(), '(' + first + #op + second + ')');\
  if (BruteForceBacktrack<T>(n, pool)) return true;\
  pool.erase(pool.begin())

template<class T>
static void Swap(T& v1, T& v2){
  T t = v1;
  v1 = v2;
  v2 = t;
}

template<class T>
static bool BruteForceBacktrack(T n, std::vector<std::string>& pool){
  if (pool.size() == 1){
    return Eq(nsolver::Calculate(pool[0]), n); //Can be different types
  }

  for (int i = 0; i < pool.size(); i++){
    std::string first = pool[i];
    pool.erase(pool.begin()+i);

    for (int j = i; j < pool.size(); j++){ //not i+1 bc erase happened line above
      std::string second = pool[j];
      pool.erase(pool.begin()+j);

      std::string curExpr;
      PERFORM(*);
      PERFORM(+);
      PERFORM(-);
      if (second != "0"){
        PERFORM(/);
      }

      Swap<std::string>(first, second);
      PERFORM(-);
      if (second != "0"){
        PERFORM(/);
      }
      Swap<std::string>(first, second);

      pool.insert(pool.begin()+j, second);
    }

    pool.insert(pool.begin()+i, first);
  }

  return false;
}

template<class T>
std::string nsolver::BruteForce(T n, std::vector<T> v){
  std::vector<std::string> pool;
  for (int i = 0; i < v.size(); i++){
    pool.push_back(std::to_string(v[i]));
  }
  if (!BruteForceBacktrack<T>(n, pool)) return "";
  return pool[0];
}

template
std::string nsolver::BruteForce<float>(float, std::vector<float>);

template
std::string nsolver::BruteForce<int>(int, std::vector<int>);
