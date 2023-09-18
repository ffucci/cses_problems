#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  int n = 0;

  cin >> n;
  vector<int> stick_lengths(n);
  for (int i = 0; i < n; ++i) {
    cin >> stick_lengths[i];
  }

  std::ranges::sort(stick_lengths);

  auto median = stick_lengths[n / 2];

  // min cost is the sum of the differences from the median
  long long int sum = 0;

  for (int i = 0; i < n; ++i) {
    sum += abs(stick_lengths[i] - median);
  }

  cout << sum << endl;
  return 0;
}