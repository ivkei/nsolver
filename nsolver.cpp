#include"nsolver.h"

#include"calc.h"
#include"logger.h"

#include<cmath>

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
  if (size > v.size()) LOG_ERROR("(Combinations) size > v.size()");
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
template<class T>
static std::vector<std::vector<T>> Permutations(std::vector<T> v, int k){
  std::vector<std::vector<T>> combs;
  std::vector<std::vector<T>> res;

  combs = Combinations(v, k);

  for (int i = 0; i < combs.size(); i++){
    auto perms = Permutations(combs[i]);
    res.insert(res.end(), perms.begin(), perms.end());
  }

  return res;
}

//Signs must also have pars
//Assumes the signs are already in proper format
//Takes in perms
static std::string ApplySigns(int n, std::vector<std::vector<int>> nums, std::vector<std::vector<char>> signs){
  for (int i = 0; i < nums.size(); i++){
    for (int j = 0; j < signs.size(); j++){
      LOG_INFO("(Iteration) i: ", i, " j: ", j);

      std::string expr;
      int l = 0; //Signs index
      if (signs[j][0] == '('){
        expr += signs[j][0];
        l=1;
      }
      expr += std::to_string(nums[i][0]);

      for (int k = 1; k < nums[j].size(); k++, l++){
        LOG_INFO("(Iteration) k: ", k, " l: ", l);

        if (l >= signs[j].size()) LOG_ERROR("l >= signs[j].size()");
        
        if (signs[j][l] == '('){
          LOG_INFO("Placing right par");
          LOG_INFO("Current k: ", signs[j][l]);
          LOG_INFO("k+1: ", signs[j][l+1]);

          if (signs[j][l+1] == ')'){
            //TODO: Account for this case
          } else{
            expr += signs[j][++l]; //Next
            expr += signs[j][l-1]; //Par
            expr += std::to_string(nums[i][k]); //Num
          }

        }else if (signs[j][l] == ')'){
          expr += signs[j][l++]; //Par
          expr += signs[j][l]; //Next op
          expr += std::to_string(nums[i][k]); //Num

        }else{
          expr += signs[j][l];
          expr += std::to_string(nums[i][k]);
        }

        LOG_INFO("Int expr: ", expr);
      }

      if (l != signs[j].size()) expr+=')'; //Place the last par

      LOG_INFO("Expr: ", expr);

      if (calc::Calculate(expr) == n) return expr;
    }
  }

  return "";
}

static std::vector<std::vector<char>> IncludePars(const std::vector<std::vector<char>>& signs){
  LOG_INFO("signs.size(): ", signs.size());
  std::vector<std::vector<char>> res;

  //TODO: multiple sets
  for (int i = 0; i < signs.size(); i++){
    std::vector<std::vector<char>> withAllPars;
    std::vector<char> cur = signs[i];

    LOG_INFO("(IncludePars Progress) ", i, "/", signs.size());

    for (int j = 0; j < cur.size(); j++){
      cur.insert(cur.begin()+j, '(');

      for (int k = j+1; k <= cur.size(); k++){
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

std::string nsolver::BruteForce(int n, std::vector<int> v){
  auto nums = Permutations<int>(v);
  auto signs = Permutations<char>({'*', '-', '+', '/'}, 3);
  signs = IncludePars(signs);
  //TODO: make work with arbitrary amount of signs (Extend combinations to produce of any size

  LOG_INFO("Got signs and terms");

  return ApplySigns(n, nums, signs);
}

