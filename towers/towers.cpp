#include <array>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

using ll = long long int;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N = 0;
  cin >> N;

  ll count = 0;
  multiset<ll> els;

  for (int i = 0; i < N; ++i) {
    ll var;
    cin >> var;
    auto itr = els.upper_bound(var);
    if (itr == els.end()) {
      els.insert(var);
    } else {
      els.erase(itr);
      els.insert(var);
    }
  }

  cout << els.size() << endl;
  return 0;
}