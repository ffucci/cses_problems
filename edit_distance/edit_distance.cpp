#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

#if 0
int solveDP(const vector<int> &prices, const vector<int> &pages, int x) {
  assert(prices.size() == pages.size());
  const auto n = prices.size();
  vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));

  for (int i = n - 1; i >= 0; --i) {
    for (int c = 0; c <= x; ++c) {
      dp[i][c] = dp[i + 1][c];
      if (c - prices[i] >= 0) {
        dp[i][c] = max(dp[i][c], pages[i] + dp[i + 1][c - prices[i]]);
      }
    }
  }

  return dp[0][x];
}
#endif

int solveRec(const std::string &s1, const std::string &s2, int i, int j,
             vector<vector<int>> &dp) {
  if (i == 0) {
    return j;
  }

  if (j == 0) {
    return i;
  }

  if (dp[i][j] != -1) {
    return dp[i][j];
  }

  if (s1[i - 1] == s2[j - 1]) {
    return dp[i][j] = solveRec(s1, s2, i - 1, j - 1, dp);
  }

  //   int add_cost = min(solveRec(s1, s2, i + 1, j, dp), solveRec(s1, s2, i, j
  //   + 1, dp)); int replace_cost = 1 + solveRec(s1, s2, i + 1, j + 1, dp);

  return dp[i][j] = 1 + min({solveRec(s1, s2, i, j - 1, dp),
                             solveRec(s1, s2, i - 1, j, dp),
                             solveRec(s1, s2, i - 1, j - 1, dp)});
}

int main() {

  // const auto result = solveRec(prices, pages, 0, x);
  std::string s1;
  std::string s2;
  std::cin >> s1 >> s2;

  vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1, -1));
  const auto result = solveRec(s1, s2, s1.size(), s2.size(), dp);
  cout << result << endl;
  return 0;
}