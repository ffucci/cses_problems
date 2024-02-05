#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

static constexpr int MOD = 1e9 + 7;

using ll = long long int;

int main() {
  int N;
  cin >> N;
  deque<ll> dq;
  vector<ll> ans(N, 0);
  vector<ll> e(N, 0);
  for (int i = 0; i < N; ++i) {
    ll var;
    cin >> var;
    e[i] = var;
  }

  for (int i = 0; i < N; ++i) {

    while (!dq.empty() && e[i] <= e[dq.front()]) {
      dq.pop_front();
    }

    if (!dq.empty()) {
      ans[i] = dq.front() + 1;
    }
    dq.push_front(i);
  }

  for (int i = 0; i < N; ++i) {
    cout << ans[i] << " ";
  }
  cout << endl;
  return 0;
}