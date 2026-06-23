#include"nsolver.h"

#include"calc.h"
#include"logger.h"

#include<string>
#include<cmath>
#include<algorithm>

template<class T>
static void BacktrackCombs(const std::vector<T>& v, int k, int start, std::vector<T>& current, std::vector<std::vector<T>>& res){
  if (current.size() == k){
    res.push_back(current);
    return;
  }

  for (int i = start; i < v.size(); i++){
    current.push_back(v[i]);
    BacktrackCombs(v, k, i+1, current, res);
    current.pop_back();
  }
}

template<class T>
static std::vector<std::vector<T>> Combinations(std::vector<T> v, int size){
  if (size > v.size()) nsolver::LOG_ERROR("(Combinations) size > v.size()");
  if (size == v.size()) return {v};

  std::vector<std::vector<T>> res;
  std::vector<T> cur;
  BacktrackCombs(v, size, 0, cur, res);

  return res;
}

template<class T>
static std::vector<std::vector<T>> Permutations(std::vector<T> v){
  if (v.size() == 1) return {v};

  std::vector<std::vector<T>> res;

  for (int i = 0; i < v.size(); i++){
  std::vector<T> vWithoutI = v;
  vWithoutI.erase(vWithoutI.begin()+i);

  auto prevPerms = Permutations<T>(vWithoutI);
    for (int j = 0; j < prevPerms.size(); j++){
      std::vector<T> newPerm = prevPerms[j];

      newPerm.insert(newPerm.begin(), v[i]);
      res.push_back(newPerm);
    }
  }

  return res;
}

//k is the size of permutations
//Permuations of all combinations
template<class T>
static std::vector<std::vector<T>> Permutations(std::vector<T> v, int k){
  std::vector<std::vector<T>> combs;
  std::vector<std::vector<T>> res;

  combs = Combinations(v, k);

  for (int i = 0; i < combs.size(); i++){

    if ((combs.size()/10 != 0) && i % (combs.size()/10) == 0){
      nsolver::LOG_INFO("(Making Permutations) ", std::round(10000*((float)i/(float)combs.size()))/100, "%");
    }

    auto perms = Permutations(combs[i]);
    res.insert(res.end(), perms.begin(), perms.end());
  }

  return res;
}

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

//Signs must also have pars
//Assumes the signs are already in proper format
//Takes in perms
template<class T>
static std::string ApplySigns(T n, std::vector<std::vector<T>> nums, std::vector<std::vector<char>> signs){
  if (nums.size() == 1 && nums[0].size() == 1 && n == nums[0][0]) return std::to_string(n); //Just 1 number

  for (int i = 0; i < nums.size(); i++){
    for (int j = 0; j < signs.size(); j++){
      std::string expr;

      if ((nums.size()*signs.size()/10 != 0) && (i*j + j) % ((nums.size()*signs.size())/10) == 0){
        nsolver::LOG_INFO("(Checked possibilities) ", std::round(10000*((float)i/(float)nums.size()))/100, "%");
      }

      //Put in the signs
      for (int k = 0; k < signs[j].size(); k++){
        expr+=signs[j][k];
      }

      //Put in the numbers
      for  (int k = 0, l = 0; k <= expr.size(); k++){
        if (k != expr.size() && expr[k] == '(') continue;
        if (k != 0 && expr[k-1] == ')') continue;
        auto num = std::to_string(nums[i][l]);
        expr.insert(expr.begin()+k, num.begin(), num.end());
        k += num.size(); //Account for pasted number
        l++;
      }

      if (Eq<float, T>(nsolver::Calculate(expr), n)) return expr;
    }
  }

  return "";
}

//Either target
static bool AllAre(std::vector<char> str, std::vector<char> tar){
  for (int i = 0; i < str.size(); i++){
    if (std::find(tar.begin(), tar.end(), str[i]) == tar.end()) return false;
  }

  return true;
}

//Variable to display progress percentage for pars, updated in bruteforce
int totalParsIterations = 1;
int curParsIterations = 0;

static std::vector<std::vector<char>> IncludePars(const std::vector<std::vector<char>>& signs){
  std::vector<std::vector<char>> res;

  for (int i = 0; i < signs.size(); i++){
    std::vector<std::vector<char>> withAllPars;
    std::vector<char> cur = signs[i];

    if (AllAre(cur, {'+'}) || AllAre(cur, {'-'}) || AllAre(cur, {'*'}) || AllAre(cur, {'+', '-'})) continue; //Optimizations

    if ((signs.size()/10 != 0) && i % (signs.size()/10) == 0){
      nsolver::LOG_INFO("(Putting Parenthesis) ",
          std::round(10000*(((float)i+((float)(curParsIterations*signs.size())))/((float)signs.size()*totalParsIterations)))/100.0f, "%");
    }

    for (int j = 0; j < cur.size(); j++){

      if (j > 0 && cur[j-1] == ')') continue; //Dont place ( after )

      cur.insert(cur.begin()+j, '(');

      for (int k = j+2; k <= cur.size(); k++){ //j+2 to avoid (()), optimization also
        if (k < cur.size() && cur[k] == '(') continue;
        cur.insert(cur.begin()+k, ')');

        withAllPars.push_back(cur);

        cur.erase(cur.begin()+k); //Erase )
      }

      cur.erase(cur.begin()+j); //Erase (
    }

    res.insert(res.end(), withAllPars.begin(), withAllPars.end());
  }

  return res;
}

template<class T>
std::string nsolver::BruteForce(T n, std::vector<T> v, int precision){
  if (!v.size()) return "";

  std::vector<char> signs = {'*', '-', '+', '/'};
  std::vector<char> signsPermuted;
  for (int i = 0; i < v.size()-1; i++){ //Copies of signs
    signsPermuted.insert(signsPermuted.end(), signs.begin(), signs.end());
  }

  nsolver::LOG_INFO("Got signs!");

  auto nums = Permutations<T>(v);
  auto signPerms = Permutations<char>(signsPermuted, v.size()-1);

  nsolver::LOG_INFO("Got permutations!");

  totalParsIterations = std::min((int)v.size()-2, precision);
  for (int i = 0; i < (int)v.size()-2 && i < precision; i++){
    curParsIterations = i;
    signPerms = IncludePars(signPerms);
  }

  nsolver::LOG_INFO("Got Pars!");

  return ApplySigns<T>(n, nums, signPerms);
}

//Predefine numerical templates (C++ doesnt do it if its in a source file)
template
std::string nsolver::BruteForce<float>(float, std::vector<float>, int precision);

template
std::string nsolver::BruteForce<int>(int, std::vector<int>, int);
