#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long int;

class FenwickTree {
public:
  explicit FenwickTree(const vector<ll> &values)
      : tree_(std::vector<ll>(values.size() + 1, 0ll)) {

    for (int i = 1; i <= values.size(); ++i) {
      update(i, values[i - 1]);
    }
  }

  void update(int k, int value) {
    while (k <= tree_.size()) {
      tree_[k] += value;
      k += k & -k;
    }
  }

  ll query(int a, int b) { return sum(b) - sum(a - 1); }

  ll get(int k) { return tree_[k]; }

private:
  std::vector<ll> tree_{};

  ll sum(ll k) {
    ll result = 0;
    while (k >= 1) {
      result += tree_[k];
      k -= k & -k;
    }

    return result;
  }
};

int main() {
  int n = 0;
  int q = 0;
  cin >> n >> q;
  vector<ll> values(n, 0ll);
  vector<vector<ll>> queries(q, vector<ll>(3, 0));

  for (int i = 0; i < n; ++i) {
    cin >> values[i];
  }

  for (int i = 0; i < q; ++i) {
    cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
  }

  FenwickTree tree(values);

  for (auto &q : queries) {
    if (q[0] == 1) {
      int k = q[1];
      int u = q[2];
      long long int delta = u - values[k - 1];
      values[k - 1] += delta;
      tree.update(k, delta);
    } else if (q[0] == 2) {
      int a = q[1];
      int b = q[2];
      cout << tree.query(a, b) << endl;
    }
  }
  return 0;
}