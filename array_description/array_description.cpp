#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

static constexpr int MOD = 1e9 + 7;

// int solveDP(const vector<int> &values, int i, int m) {
//   if (i == values.size()) {
//     return 0;
//   }

//   int ans = 0;
//   for (int j = 1; j <= m; ++j) {
//     // cout << j << " ";
//     auto val1 = 0;
//     auto val2 = 0;

//     if (i > 0 && values[i - 1] > 0) {
//       val1 = std::abs(j - values[i - 1]);
//     }

//     if (i < values.size() - 1 && values[i + 1] > 0) {
//       val2 = std::abs(j - values[i + 1]);
//     }

//     if (val1 <= 1 && val2 <= 1) {
//       ans += 1 + solveDP(values, i + 1, m);
//     }
//   }

//   return ans;
// }

int solveDP(const vector<int> &values, int i, int prev_value, int m,
            vector<vector<int>> &dp) {
  if (i == values.size()) {
    return 1;
  }

  if (dp[i][prev_value] != -1) {
    return dp[i][prev_value];
  }
  // cout << "i: " << i << ", prev_value: " << prev_value << endl;
  // if (abs(prev_value - values[i]) > 1) {
  //   return 0;
  // }

  int ans = 0;
  if (values[i] == 0) {
    int left = i == 0 ? 1 : max(1, prev_value - 1);
    int right = i == 0 ? m : min(prev_value + 1, m);

    for (int j = left; j <= right; ++j) {
      if (i == 0 || abs(j - prev_value) <= 1) {
        ans = (ans + solveDP(values, i + 1, j, m, dp)) % MOD;
      }
    }
  } else {
    if (i == 0 || abs(values[i] - prev_value) <= 1) {
      ans = (ans + solveDP(values, i + 1, values[i], m, dp)) % MOD;
    }
  }
  return dp[i][prev_value] = ans;
}

int solveDPLinear(const vector<int> &values, int m) {
  const auto n = values.size();
  vector<vector<int>> dp(n, vector<int>(m + 1, 0));

  if (values[n - 1] == 0) {
    for (int j = 1; j <= m; ++j) {
      dp[n - 1][j] = 1;
    }
  } else {
    dp[n - 1][values[n - 1]] = 1;
  }

  for (int i = n - 2; i >= 0; --i) {
    if (values[i] == 0) {

      for (int j = 1; j <= m; ++j) {
        if (j - 1 > 0)
          dp[i][j] = (dp[i][j] + dp[i + 1][j - 1]) % MOD;

        if (j + 1 <= m)
          dp[i][j] = (dp[i][j] + dp[i + 1][j + 1]) % MOD;

        dp[i][j] = (dp[i][j] + dp[i + 1][j]) % MOD;
      }
    } else {
      if (values[i] - 1 > 0)
        dp[i][values[i]] = (dp[i][values[i]] + dp[i + 1][values[i] - 1]) % MOD;
      if (values[i] + 1 <= m)
        dp[i][values[i]] = (dp[i][values[i]] + dp[i + 1][values[i] + 1]) % MOD;
      dp[i][values[i]] = (dp[i][values[i]] + dp[i + 1][values[i]]) % MOD;
    }
  }

  int ans = 0;
  for (int i = 1; i <= m; i++) {
    ans = (ans + dp[0][i]) % MOD;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n = 0;
  int m = 0;
  cin >> n >> m;
  vector<int> values(n, 0);
  for (int i = 0; i < n; ++i) {
    cin >> values[i];
  }

  // vector<vector<int>> dp(n, vector<int>(m + 1, -1));
  auto ans = solveDPLinear(values, m);
  cout << ans << endl;
  return 0;
}