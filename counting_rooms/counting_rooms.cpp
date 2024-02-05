#include <array>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class CountingRooms {

public:
  explicit CountingRooms(vector<string> board) : board_(std::move(board)) {}

  int solve() {
    const int n = board_.size();
    const int m = board_[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int count = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board_[i][j] == '.' && !visited[i][j]) {
          run_bfs(i, j, visited);
          ++count;
        }
      }
    }

    return count;
  }

private:
  void run_bfs(int i, int j, vector<vector<bool>> &visited) {
    queue<vector<int>> q;
    q.push({i, j});
    visited[i][j] = true;
    while (!q.empty()) {
      auto curr = q.front();
      int x = curr[0];
      int y = curr[1];
      q.pop();

      for (int k = 0; k < 4; ++k) {
        int ni = x + dx[k];
        int nj = y + dy[k];

        if (can_visit(board_, visited, ni, nj)) {
          visited[ni][nj] = true;
          if (board_[ni][nj] == '.') {
            q.push({ni, nj});
          }
        }
      }
    }

    return;
  }

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

  static constexpr auto can_visit = [](const vector<string> &board,
                                       const vector<vector<bool>> &visited,
                                       int i, int j) {
    return i >= 0 && i < board.size() && j >= 0 && j < board[0].size() &&
           visited[i][j] == false && board[i][j] == '.';
  };

  static constexpr std::array<int, 4> dx = {1, 0, -1, 0};
  static constexpr std::array<int, 4> dy = {0, 1, 0, -1};
  vector<string> board_;
};

int main() {
  int n = 0;
  int m = 0;
  cin >> n;
  cin >> m;
  vector<string> board;

  for (int i = 0; i < n; ++i) {
    std::string s;
    cin >> s;
    board.push_back(s);
  }

  CountingRooms solution(board);
  auto result = solution.solve();
  std::cout << result << std::endl;
  return 0;
}