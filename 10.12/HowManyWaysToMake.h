#ifndef HOW_MANY_WAYS_TO_MAKE_H
#define HOW_MANY_WAYS_TO_MAKE_H

// TODO: Your answer for question 1a goes here

#include <vector>
using std::vector;

int howManyWaysToMake(int money, vector<int> coins) {
	//using dynamic programming to solve knapsack problem
	//the ways of the first i coins making the amount of j money
    vector<vector<int> > dp(coins.size() + 1, vector<int>(money + 1, 0));
    dp[0][0] = 1; //initialize that, 1 way of 0 coin to make 0 money
    for(int i = 0; i < coins.size(); ++i) {
        int coin = coins[i];
        for(int j = 0; j <= money; ++j) {
            dp[i + 1][j] += dp[i][j];
            if(j >= coin) dp[i + 1][j] += dp[i + 1][j - coin];
        }
    }
    int possibilities = dp[coins.size()][money];
    return possibilities;
}

// Do not write any code below this line

#endif
