#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n = 0;
  int x = 0;

  cin >> n >> x;

  vector<int> elements(n, 0);

  for (int i = 0; i < n; ++i) {
    cin >> elements[i];
  }

  unordered_map<int, int> mp{};

  for (int i = 0; i < n; ++i) {
    int el = elements[i];
    if (mp.contains(x - el)) {
      cout << i + 1 << " " << mp[x - el] + 1 << endl;
      return 0;
    }
    mp[el] = i;
  }

  cout << "IMPOSSIBLE" << endl;
  return 0;
}