#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

static constexpr int MOD = 1e9 + 7;

using ll = long long int;
using plb = std::pair<ll, bool>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N = 0;
  cin >> N;

  vector<plb> events;

  for (int i = 0; i < N; ++i) {
    ll start = 0;
    ll end = 0;
    cin >> start >> end;
    events.emplace_back(start, true);
    events.emplace_back(end, false);
  }

  sort(begin(events), end(events));

  ll checked_in = 0;

  ll maxi = 0;
  for (auto &event : events) {
    if (event.second == true) {
      checked_in++;
    } else {
      checked_in--;
    }
    maxi = max(maxi, checked_in);
  }
  cout << maxi << endl;
  return 0;
}