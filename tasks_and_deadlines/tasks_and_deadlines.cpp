#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

static constexpr int MOD = 1e9 + 7;

using ll = long long int;
using pll = std::pair<ll, ll>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N = 0;
  cin >> N;

  vector<pll> events(N);

  for (int i = 0; i < N; ++i) {
    ll duration = 0;
    ll deadline = 0;
    cin >> duration >> deadline;
    events[i].first = duration;
    events[i].second = deadline;
  }

  sort(begin(events), end(events));

  ll total = 0;
  ll current_time = 0;
  for (auto &event : events) {
    current_time += event.first;
    total += event.second - current_time;
  }
  cout << total << endl;
  return 0;
}