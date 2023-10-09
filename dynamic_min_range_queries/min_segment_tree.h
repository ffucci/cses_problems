#pragma once

#include <concepts>
#include <vector>

#include <iostream>

namespace ff::cp::tree {

long long next_power_of_2(long long N) {
  // if N is a power of two simply return it
  if (!(N & (N - 1)))
    return N;
  // else set only the left bit of most significant bit
  return 0x8000000000000000 >> (__builtin_clzll(N) - 1);
}

template <std::integral T, std::invocable<T, T> Predicate> class SegmentTree {
public:
  explicit SegmentTree(const std::vector<T> &values,
                       std::invocable<T, T> auto &&comparator) {
    const auto n = next_power_of_2(values.size());
    // std::cout << "selected size: " << 2 * next_pow2 << endl;
    tree_.resize(2 * n, std::numeric_limits<T>::max());
    std::copy(std::begin(values), std::end(values), std::begin(tree_) + n);
    segment_op_ = comparator;
    // build the tree (first n-1 elements are for the tree)
    // last is for the array;
    build();
  }

  T query(int l, int r) { // sum on interval [l, r)
    T result = std::numeric_limits<T>::max();
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
    tree_[k] = value;
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