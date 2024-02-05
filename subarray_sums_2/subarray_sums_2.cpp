#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

static constexpr int MOD = 1e9 + 7;

using ll = long long int;

int main() {
  unordered_map<ll, ll> pref;
  int N, target;
  cin >> N >> target;
  ll sum = 0;
  ll count = 0;
  pref[0] = 1;
  for (int i = 0; i < N; ++i) {
    ll var;
    cin >> var;
    sum += var;
    auto itr = pref.find(sum - target);
    if (itr != pref.end()) {
      count += itr->second;
    }

    pref[sum]++;
  }
  cout << count << endl;
  return 0;
}