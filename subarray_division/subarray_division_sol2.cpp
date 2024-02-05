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
  int N;
  cin >> N;
  ll sum = 0;
  pref[0] = 1;
  for (int i = 0; i < N; ++i) {
    ll var;
    cin >> var;
    sum = ((sum + var) % N + N) % N;
    pref[sum]++;
  }

  ll count = 0;
  // count all the possible pairs that can be formed with sums in the array
  for (auto [k, v] : pref) {
    count += v * (v - 1) / 2;
  }
  cout << count << endl;
  return 0;
}