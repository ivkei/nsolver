#include"nsolver.h"

#include"calc.h"
#include"logger.h"

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

//Return "Nothing was found" if --guess what??-- nothing was found
std::string nsolver::SolveBT(int n, std::vector<int> v){
  auto vPerms = Permutations<int>(v);
  auto signPerms = Permutations<char>({'(', ')', '*', '-', '+', '/'});

  LOG_INFO("Got permutations");

  for (int i = 0; i < vPerms.size(); i++){
    for (int j = 0; j < signPerms.size(); j++){
      LOG_INFO("(Iteration) i: ", i, " j: ", j);

      bool rightParPlaced = false;
      bool leftSkipped = false;
      std::string expr;
      int k = 0;
      int l = 1;
      if (signPerms[j][0] == '('){
        expr += signPerms[j][0];
        rightParPlaced = true;
        k=1;
      }
      expr += std::to_string(vPerms[i][0]);

      for (; k < signPerms[j].size() && l < vPerms[i].size(); k++, l++){
        LOG_INFO("(Iteration) k: ", k, " l: ", l);
        
        if (signPerms[j][k] == '('){
          LOG_INFO("Placing right par");
          LOG_INFO("Current k: ", signPerms[j][k]);
          LOG_INFO("k+1: ", signPerms[j][k+1]);
          expr += signPerms[j][++k];
          if (leftSkipped) {
            expr += std::to_string(vPerms[i][l]);
            continue;
          }
          expr += signPerms[j][k-1];
          expr += std::to_string(vPerms[i][l]);
          rightParPlaced = true;

        }else if (signPerms[j][k] == ')'){
          if (!rightParPlaced){
            leftSkipped = true;
            expr += signPerms[j][++k];
            expr += std::to_string(vPerms[i][l]);
            continue;
          }
          expr += signPerms[j][k++];
          expr += (k != signPerms[j].size() ? signPerms[j][k] : ' ');
          expr += std::to_string(vPerms[i][l]);

        }else{
          expr += signPerms[j][k];
          expr += std::to_string(vPerms[i][l]);
        }

        LOG_INFO("Int expr: ", expr);
      }

      //Last par (or before last)
      LOG_INFO("Last sign: ", signPerms[j][signPerms[j].size()-1]);
      if (signPerms[j][signPerms[j].size()-1] == '(' || signPerms[j][signPerms[j].size()-1] == ')') expr += signPerms[j][signPerms[j].size()-1];
      if (signPerms[j][signPerms[j].size()-2] == '(' || signPerms[j][signPerms[j].size()-2] == ')') expr += signPerms[j][signPerms[j].size()-2];
      LOG_INFO("Int expr: ", expr);

      //Swap pars if they are in the wrong order
      int rightParIndex = -1;
      int leftParIndex = -1;
      for (int m = 0; m < expr.size(); m++){
        if (expr[m] == '(') leftParIndex = m;
        if (expr[m] == ')') rightParIndex = m;
      }
      if (leftParIndex != -1 && rightParIndex!= -1 && leftParIndex > rightParIndex){
        expr[leftParIndex] = ')';
        expr[rightParIndex] = '(';
      }
      //If only 1 was found, remove
      if (leftParIndex == -1 && rightParIndex != -1){
        expr.erase(expr.begin() + rightParIndex);
      }
      if (leftParIndex != -1 && rightParIndex == -1){
        expr.erase(expr.begin() + leftParIndex);
      }

      LOG_INFO("Expr: ", expr);

      if (calc::Calculate(expr) == n) return expr;
    }
  }

  return "Nothing was found";
}

