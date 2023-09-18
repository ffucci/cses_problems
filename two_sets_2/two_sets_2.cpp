#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

static constexpr int MOD = 1e9 + 7;

long long int two_sets_2_rec(long long int current_idx,
                             long long int current_sum, long long int n,
                             vector<vector<int>> &dp) {
  if (current_idx > n) {
    return 0;
  }
  if (current_sum == 0) {
    return 1;
  }

  if (current_sum < 0) {
    return 0;
  }

  if (dp[current_idx][current_sum] != -1) {
    return dp[current_idx][current_sum];
  }

  long long int without_value =
      two_sets_2_rec(current_idx + 1, current_sum, n, dp);
  long long int with_value = 0;
  if (current_sum - current_idx >= 0) {
    with_value =
        two_sets_2_rec(current_idx + 1, current_sum - current_idx, n, dp);
  }
  return dp[current_idx][current_sum] = (with_value + without_value) % MOD;
}

int main() {
  int n = 0;
  cin >> n;

  int sum = n * (n + 1) / 2;
  if (sum % 2 != 0) {
    cout << 0 << endl;
    return 0;
  }
  int target = sum / 2;
  vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
  auto ans = two_sets_2_rec(1, target, n, dp);
  cout << ans << endl;
  return 0;
}