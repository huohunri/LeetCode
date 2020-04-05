#include <stdio.h>
#include <stdlib.h>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string> // std::string
#include <iostream> // std::cout
#include <sstream> // std::stringstream, std::stringbuf

using namespace std;
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        //int coins[] = {1,5,10,25};
        int coinssize = coins.size();
        int n = amount;
        int dp[coinssize][n+1];
        for (int i = 0; i < coinssize; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < coins.size(); i++) {
            for (int j = 0; j <= n; j++) {
                if (j >= coins[i]) {
                    dp[i][j] = (dp[i-1][j] + dp[i][j-coins[i]])%1000000007;
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[coinssize-1][n];
    }
};


void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

int stringToInteger(string input) {
    return stoi(input);
}

int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> coins = stringToIntegerVector(line);
        getline(cin, line);
        int amount = stringToInteger(line);
        
        int ret = Solution().coinChange(coins,amount);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}