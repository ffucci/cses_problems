#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

using pii = pair<int, int>;

int main() {
  int n = 0;
  int x = 0;

  cin >> n >> x;

  vector<pii> elements(n);
  unordered_map<int, int> pos{};
  for (int i = 0; i < n; ++i) {
    int val = 0;
    cin >> val;
    elements[i] = make_pair(val, i);
  }

  std::ranges::sort(elements);

  for (int i = 0; i < n; ++i) {
    auto itr = std::lower_bound(
        begin(elements) + i + 1, end(elements), x - elements[i].first,
        [](const auto &el1, const int el2) { return el1.first < el2; });
    if (itr != elements.end() && itr->first == x - elements[i].first) {
      cout << elements[i].second + 1 << " " << itr->second + 1 << endl;
      return 0;
    }
  }

  cout << "IMPOSSIBLE" << endl;
  return 0;
}