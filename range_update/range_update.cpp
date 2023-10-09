#include <concepts>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;
using ll = long long int;

namespace ff::cp::tree {

long long next_power_of_2(long long N) {
  // if N is a power of two simply return it
  if (!(N & (N - 1)))
    return 2 * N;
  // else set only the left bit of most significant bit
  return 0x8000000000000000 >> (__builtin_clzll(N) - 1);
}

template <std::integral T, std::invocable<T, T> Predicate> class SegmentTree {
public:
  explicit SegmentTree(const std::vector<T> &values,
                       std::invocable<T, T> auto &&comparator) {
    const auto n = next_power_of_2(values.size());
    tree_.resize(2 * n, 0);
    std::copy(std::begin(values), std::end(values), std::begin(tree_) + n);
    segment_op_ = comparator;
    build();
  }

  T query(int l, int r) { // sum on interval [l, r)
    T result = 0;
    const int n = tree_.size();
    l += n / 2;
    r += n / 2;

    while (l <= r) {
      if (l % 2 == 1)
        result = segment_op_(result, tree_[l++]);
      if (r % 2 == 0)
        result = segment_op_(result, tree_[r--]);

      l >>= 1;
      r >>= 1;
    }
    return result;
  }

  void modify(int k, T value) { // set value at position p
    auto n = tree_.size();
    n >>= 1;
    k += n; // correct the offset
    tree_[k] += value;
    // we first correct the initial position of the pointer than we can start
    // the update
    for (k /= 2; k > 1; k >>= 1)
      tree_[k] = segment_op_(tree_[2 * k], tree_[2 * k + 1]);
  }

  void print_tree() {
    for (auto &val : tree_) {
      std::cout << val << " ";
    }

    std::cout << std::endl;
  }

private:
  void build() { // build the tree
    auto n = tree_.size();
    n >>= 1;
    for (size_t i = n - 1; i > 0; --i) {
      tree_[i] = segment_op_(tree_[2 * i], tree_[2 * i + 1]);
    }
  }

  Predicate segment_op_;
  std::vector<T> tree_{};
};

} // namespace ff::cp::tree

int main() {
  int n = 0;
  int q = 0;
  constexpr bool DEBUG{false};

  cin >> n >> q;
  vector<ll> values(n, 0ll);
  vector<ll> diff(values.size(), 0ll);
  vector<vector<ll>> queries(q, vector<ll>(4, 0));

  for (int i = 0; i < n; ++i) {
    cin >> values[i];
  }

  diff[0] = values[0];
  for (int i = 1; i <= n; ++i) {
    diff[i] = values[i] - values[i - 1];
  }

  if constexpr (DEBUG) {
    for (auto &v : values) {
      cout << v << " ";
    }
    cout << endl;

    for (auto &v : diff) {
      cout << v << " ";
    }
    cout << endl;
  }

  for (int i = 0; i < q; ++i) {
    cin >> queries[i][0];
    if (queries[i][0] == 1) {
      cin >> queries[i][1] >> queries[i][2] >> queries[i][3];
    } else if (queries[i][0] == 2) {
      cin >> queries[i][1];
    }
  }

  auto op = [](ll left, ll right) { return left + right; };
  ff::cp::tree::SegmentTree<ll, decltype(op)> segment_tree(diff, op);

  if constexpr (DEBUG) {
    cout << "#########################" << endl;
    segment_tree.print_tree();
    cout << "#########################" << endl;
  }
  for (auto q : queries) {
    if (q[0] == 1) {
      segment_tree.modify(q[1] - 1, q[3]);
      segment_tree.modify(q[2], -q[3]);
    } else if (q[0] == 2) {
      std::cout << segment_tree.query(0, q[1] - 1) << std::endl;
    }

    if constexpr (DEBUG) {
      segment_tree.print_tree();
    }
  }
  return 0;
}