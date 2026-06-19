#include"calc.h"

#include"logger.h"

#include<vector>
#include<cmath>

struct Operator{
  char symbol;
  int priority;
};

static int Priority(char symbol){
  switch (symbol){
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
    case 'x':
      return 2;
    default:
      LOG_WARNING("Wrong symbol put into Priority()");
      return -1;
  }
}

//Par isnt a sign
static int IsSign(std::string expr, int i){
    return expr[i] == '*' ||
           (expr[i] == '-' && i != 0 && !IsSign(expr, i-1)) || //not negative sign
           expr[i] == '+' ||
           expr[i] == '/' ||
           expr[i] == 'x';
}

static float StringToFloat(std::string str){
  float nParsed = 0;
  int nAfterPeriod = 0;
  bool negate = false;

  for (int i = 0; i < str.size(); i++){
    if (str[i] == '.'){
      nAfterPeriod = 1;
      continue;
    }

    if (str[i] == '-'){
      negate = !negate;
      continue;
    }

    if (!nAfterPeriod){
      nParsed*=10;
      nParsed+=(static_cast<int>(str[i]) - static_cast<int>('0'));
    } else{
      nParsed+=(static_cast<int>(str[i]) - static_cast<int>('0'))*std::pow(10, -(nAfterPeriod++));
    }
  }

  LOG_INFO("StringToFloat() parsed: ", nParsed);
  return nParsed * (negate ? -1 : 1);
}

static auto GetOpFunc(Operator op){
  return [op](float f1, float f2){
    switch(op.symbol){
      case '*': return f1*f2;
      case 'x': return f1*f2;
      case '/': return f1/f2;
      case '+': return f1+f2;
      case '-': return f1-f2;
      default:
        LOG_WARNING("Unknown operator");
        return -1.0f;
    }
  };
}

static bool CanPerformPrev(std::vector<Operator> ops, std::vector<float> nums){
  int n = ops.size();
  return (n > 1 && nums.size() > 2) && (ops[n-2].priority >= ops[n-1].priority);
}

//Performs top operation from ops with 2 nums, doesnt check, assumes ops and nums are operatable on
static void PerformCur(std::vector<Operator>& ops, std::vector<float>& nums){
  Operator cur = ops[ops.size()-1];
  ops.pop_back();

  float f1 = nums[nums.size()-2];
  float f2 = nums[nums.size()-1];

  nums.pop_back();
  nums.pop_back();

  float res = GetOpFunc(cur)(f1, f2);
  nums.push_back(res); // Put the result back

  LOG_INFO("Performed: ", f1, ' ', cur.symbol, ' ', f2, " = ", res);
}

float calc::Calculate(std::string expr){
  //Stacks for calculations
  std::vector<Operator> ops;
  std::vector<float> nums;

  //Remove all spaces
  for (int i = 0; i < expr.size(); i++){
    if (expr[i] == ' ') {
      expr.erase(i, 1);
      i--; //Account for shift after erase
    }
  }
  
  //Over every char
  for (int i = 0; i < expr.size(); i++){
    LOG_INFO("Iteration: ", i, "\tExpr: ", expr);

    //Ops into stack
    if (IsSign(expr, i)){
      Operator currentSign = {expr[i], Priority(expr[i])};
      ops.push_back(currentSign);
      LOG_INFO("Operator: ", expr[i]);
      continue;
    }

    if (expr[i] == '('){ //Both pars
      int j = i+1;
      int parsInParsCount = 0;

      for (; j < expr.size(); j++){
        if (expr[j] == '(') parsInParsCount++;
        if (expr[j] == ')' && !(parsInParsCount--)){
          std::string inPars = expr.substr(i+1, j-i-1);
          float res = Calculate(inPars);

          LOG_INFO("calc::Calculate() recursive res: ", res);

          nums.push_back(res);
          break;
        }
      }

      i = j;
      continue;
    }

    //Parsing numbers
    if ((static_cast<int>(expr[i]) >= static_cast<int>('0') && static_cast<int>(expr[i]) <= static_cast<int>('9')) || expr[i] == '-' || expr[i] == '.'){ //Checks
      int j = i;
      std::string parsed;

      for (; j < expr.size(); j++){
        if (IsSign(expr, j)){
          j--; //Undo to handle sign in next iteration
          break;
        }
        parsed+=expr[j];
      }
      nums.push_back(StringToFloat(parsed));

      //Perform previous?
      if (CanPerformPrev(ops, nums)){
        Operator curOp = ops[ops.size()-1];
        float curNum = nums[nums.size()-1];
        ops.pop_back();
        nums.pop_back();

        PerformCur(ops, nums);

        ops.push_back(curOp);
        nums.push_back(curNum);
      }

      i = j;
      continue;
    }

    LOG_WARNING("Unknown char was found in expr in calc::Calculate()");

  }

  while (!ops.empty() && nums.size() > 1){
    LOG_INFO("(After loop) Ridding of left overs");
    PerformCur(ops, nums);
  }

  if (!nums.size()) LOG_ERROR("Invalid input to calc::Calculate(), no nums were computed!");

  LOG_INFO("End of calc::Calculate() res: ", nums[0]);

  return nums[0];
}
