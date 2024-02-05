#include <array>
#include <iostream>
#include <iterator>
#include <optional>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Labyrinth {

public:
  explicit Labyrinth(vector<string> board) : board_(std::move(board)) {}

  std::optional<std::string> solve() {
    const int n = board_.size();
    const int m = board_[0].size();
    int start_x = -1;
    int start_y = -1;
    int end_x = -1;
    int end_y = -1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board_[i][j] == 'A') {
          start_x = i;
          start_y = j;
        }

        if (board_[i][j] == 'B') {
          end_x = i;
          end_y = j;
        }
      }
    }

    return run_bfs(start_x, start_y, end_x, end_y);
  }

private:
  std::optional<std::string> run_bfs(int i, int j, int bx, int by) {
    queue<vector<int>> q;
    vector<vector<int>> prev(board_.size(), vector<int>(board_[0].size(), -1));
    q.push({i, j, 0});
    board_[i][j] = 'x';
    while (!q.empty()) {
      auto curr = q.front();
      int x = curr[0];
      int y = curr[1];
      int dist = curr[2];
      q.pop();
      if (x == bx && y == by) {
        cout << "YES" << endl;
        cout << dist << endl;
        auto path = reconstruct_path(prev, x, y);
        return path;
      }

      for (int k = 0; k < 4; ++k) {
        int ni = x + dx[k];
        int nj = y + dy[k];

        if (can_visit(board_, ni, nj)) {
          board_[ni][nj] = 'x';
          prev[ni][nj] = k;
          q.push({ni, nj, dist + 1});
        }
      }
    }

    return std::nullopt;
  }

  auto reconstruct_path(vector<vector<int>> &prev, int i, int j) -> string {

    int rev = prev[i][j];
    string path;

    while (rev != -1) {
      path.push_back(dirs[rev]);
      i -= dx[rev];
      j -= dy[rev];
      rev = prev[i][j];
    }
    reverse(path.begin(), path.end());
    return path;
  }

  static constexpr auto can_visit = [](const vector<string> &board, int i,
                                       int j) {
    return i >= 0 && i < board.size() && j >= 0 && j < board[0].size() &&
           (board[i][j] == '.' || board[i][j] == 'B');
  };

  static constexpr std::array<int, 4> dy = {1, 0, -1, 0};
  static constexpr std::array<int, 4> dx = {0, 1, 0, -1};
  static constexpr std::array<char, 4> dirs = {'R', 'D', 'L', 'U'};

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

  Labyrinth solution(board);
  auto result = solution.solve();
  std::cout << (result ? result.value() : "NO") << std::endl;
  return 0;
}