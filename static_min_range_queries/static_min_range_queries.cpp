#include "segment_tree.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;
using ll = long long int;

int main() {
  int n = 0;
  int q = 0;
  cin >> n >> q;
  vector<ll> values(n, 0ll);
  vector<vector<ll>> queries(q, vector<ll>(2, 0));

  for (int i = 0; i < n; ++i) {
    cin >> values[i];
  }

  for (int i = 0; i < q; ++i) {
    cin >> queries[i][0] >> queries[i][1];
  }

  auto cmp = [](ll left, ll right) { return min(left, right); };
  ff::cp::tree::SegmentTree<ll, decltype(cmp)> segment_tree(values, cmp);
  for (auto q : queries) {
    std::cout << segment_tree.query(q[0] - 1, q[1] - 1) << endl;
  }
  return 0;
}