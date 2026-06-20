#include"nsolver.h"

#include"calc.h"
#include"logger.h"

#include<string>

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
//Permuations of all combinations
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
      LOG_INFO("===(Iteration) i: ", i, " j: ", j, "===");
      std::string expr;

      //Put in the signs
      for  (int k = 0; k < signs[j].size(); k++){
        expr+=signs[j][k];
      }

      LOG_INFO("Expr after signs: ", expr);

      //Put in the numbers
      for  (int k = 0, l = 0; k <= expr.size(); k++){
        LOG_INFO("===(Iteration) k: ", k, " l: ", l, "===");
        if (k != expr.size() && expr[k] == '(') continue;
        if (k != 0 && expr[k-1] == ')') continue;
        auto num = std::to_string(nums[i][l]);
        expr.insert(expr.begin()+(k++), num.begin(), num.end());
        l++;

        LOG_INFO("Expr in nums loop: ", expr);
      }

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

