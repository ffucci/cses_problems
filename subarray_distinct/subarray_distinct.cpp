#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

static constexpr int MOD = 1e9 + 7;

using ll = long long int;

ll solve(const vector<ll> &e, ll N, ll k, bool has_to_count = true) {
  ll l = 0;
  ll r = 0;
  ll count = 0;
  unordered_map<ll, ll> pref;
  while (r < N) {
    pref[e[r]]++;
    if (pref.size() > k) {
      auto diff = (r - l + 1);
      count += diff * (diff - 1) / 2;
      while (l < r && pref.size() > k) {

        pref[e[l]]--;
        if (pref[e[l]] == 0) {
          pref.erase(e[l]);
        }

        ++l;
      }

      diff = (r - l + 1);
      count -= diff * (diff - 1) / 2;
    }

    ++r;
  }

  if (has_to_count) {
    auto diff = (r - l + 1);
    count += diff * (diff - 1) / 2;
  }

  return count;
}

int main() {
  int N, k;
  cin >> N >> k;
  ll sum = 0;
  ll count = 0;
  vector<ll> e(N);
  for (int i = 0; i < N; ++i) {
    cin >> e[i];
  }

  ll l = 0;
  ll r = 0;
  auto result = solve(e, N, k);
  cout << result << endl;
  return 0;
}