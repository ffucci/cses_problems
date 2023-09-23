#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long int;

int main() {
  int n = 0;
  int q = 0;
  cin >> n >> q;
  vector<ll> values(n + 1, 0ll);
  vector<vector<ll>> queries(q, vector<ll>(2, 0));

  for (int i = 1; i <= n; ++i) {
    cin >> values[i];
  }

  for (int i = 0; i < q; ++i) {
    cin >> queries[i][0] >> queries[i][1];
  }

  for (int i = 1; i <= n; ++i) {
    values[i] += values[i - 1];
  }

  for (auto qu : queries) {
    cout << (values[qu[1]] - values[qu[0] - 1]) << endl;
  }

  return 0;
}