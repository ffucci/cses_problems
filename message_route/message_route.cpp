#include <array>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class MessageRoute {

public:
  explicit MessageRoute(vector<vector<int>> topo) : adj(std::move(topo)) {}

  void solve() {
    int start = 0;

    unordered_set<int> seen;
    queue<vector<int>> q;
    q.push({start, 0});
    seen.insert(start);
    vector<int> prev(adj.size(), -1);

    while (!q.empty()) {
      auto curr = q.front();
      q.pop();

      if (curr[0] == adj.size() - 1) {
        cout << curr[1] + 1 << endl;
        auto res = reconstruct_path(prev, curr[0]);
        for (auto &el : res) {
          cout << el << " ";
        }
        cout << endl;
        return;
      }

      for (auto &n : adj[curr[0]]) {
        if (seen.count(n) == 0) {
          seen.insert(n);
          q.push({n, curr[1] + 1});
          prev[n] = curr[0];
        }
      }
    }

    cout << "IMPOSSIBLE" << endl;
    return;
  }

private:
  auto reconstruct_path(vector<int> &prev, int end) -> std::vector<int> {

    int rev = prev[end];
    vector<int> path;
    path.push_back(end + 1);
    while (rev != -1) {
      path.push_back(rev + 1);
      rev = prev[rev];
    }
    reverse(path.begin(), path.end());
    return path;
  }

  vector<vector<int>> adj;
};

int main() {
  int n = 0;
  int m = 0;
  cin >> n;
  cin >> m;
  vector<vector<int>> topo(n);
  // cout << n << " " << m << endl;
  for (int i = 0; i < m; ++i) {
    int x = 0;
    int y = 0;

    cin >> x >> y;
    // cout << x << " " << y << endl;
    x--;
    y--;
    topo[x].push_back(y);
    topo[y].push_back(x);
  }

  MessageRoute solution(topo);
  solution.solve();
  return 0;
}