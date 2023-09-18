#include <cassert>
#include <climits>

#include <iostream>
#include <vector>

using namespace std;

static constexpr int MOD = 1e9 + 7;

auto solve(const vector<int> &weights, int n) {

  long long int min_group = LONG_LONG_MAX;
  for (int i = 0; i < (1 << n); ++i) {
    long long int group1 = 0;
    long long int group2 = 0;

    for (int j = 0; j < n; ++j) {
      if (i & (1 << j)) {
        group1 += weights[j];
      } else {
        group2 += weights[j];
      }
    }

    min_group = min(min_group, abs(group1 - group2));
  }

  return min_group;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n = 0;
  cin >> n;
  vector<int> weights(n, 0);
  for (int i = 0; i < n; ++i) {
    cin >> weights[i];
  }

  auto ans = solve(weights, n);
  cout << ans << endl;
  return 0;
}