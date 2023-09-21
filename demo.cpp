//
//  demo.cpp
//  demo
//
//  Created by abzar afet on 7/14/23.
//
#include <iostream>
#include <math.h>
#include <vector>

bool IsDigitInTheSet[10] = {false};

int isConcatenation(int target){
    int digitCount = 0;
    if(target == 0) {
        return IsDigitInTheSet[0] ? 1 : -1;
    }
    while(target && IsDigitInTheSet[target % 10]){
        target /= 10;
        digitCount++;
    }
    return target == 0 ? digitCount : -1;
}

std::string solution(std::vector<int> &operant1Parent, std::vector<int> &operant2Parent, std::vector<int> &operator_, int target) {
    if(operator_[target] == -1) {
        return std::to_string(target);
    }
    return solution(operant1Parent, operant2Parent, operator_, operant1Parent[target])
    + (operator_[target] == 0 ? "+":"*")
+
    solution(operant1Parent, operant2Parent, operator_, operant2Parent[target]);
}

std::string optimalSolution(std::vector<int> digitsSet, int target){
    std::vector<int> dp(target + 1, -1);
    std::vector<int> operant1Parent(target + 1, -1);
    std::vector<int> operant2Parent(target + 1, -1);
    std::vector<int> operator_(target + 1, -1); // 0: add, 1: multiply
    for(int i = 0; i <= target; i++){
        // first check if the current target number is a concatenation
        // of digits in digits set S, since concatenation is always
        // optimal than arithmetic expression.
        if((dp[i] = isConcatenation(i)) != -1)
            continue;
        for(int j = 1; j < i; j++){
            if(dp[j] == -1) // no solution found for j
                continue;
            // if i is divisible by j and i / j has a solution
            // and i / j is not computed with addition
            if(i % j == 0 && dp[i / j] != -1 && operator_[i / j] != 0) {
                if(dp[i] == -1 || dp[i] > dp[i / j] + dp[j] + 1) {
                    dp[i] = dp[i / j] + dp[j] + 1;
                    operant1Parent[i] = i / j;
                    operant2Parent[i] = j;
                    operator_[i] = 1;
                }
            }
            // if i - j has a solution
            if(dp[i - j] != -1){
                if(dp[i] == -1 || dp[i] > dp[i - j] + dp[j] + 1) {
                    dp[i] = dp[i - j] + dp[j] + 1;
                    operant1Parent[i] = i - j;
                    operant2Parent[i] = j;
                    operator_[i] = 0;
                }
            }
        }
    }
    if(dp[target] != -1){
        return solution(operant1Parent, operant2Parent, operator_, target);
    }
    return "N";
}

int main() {
    std::vector<int> digitSets = {1,4,7};
    int target = 23;
    
    for(auto digit : digitSets)
        IsDigitInTheSet[digit] = true;
    
    std::cout << optimalSolution(digitSets, target) << std::endl;
}
