#include <array>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void print_board(const vector<vector<char>> &board, int n, int m) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << board[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void solve(vector<vector<char>> &board, int n, int m) {

  queue<vector<int>> q;
  int start_x = -1;
  int start_y = -1;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (board[i][j] == 'M') {
        q.push({i, j});
      } else if (board[i][j] == 'A') {
        start_x = i;
        start_y = j;
      }
    }
  }

  q.push({start_x, start_y});

  const array<int, 4> dx = {1, 0, -1, 0};
  const array<int, 4> dy = {0, -1, 0, 1};
  const array<char, 4> dirs = {'D', 'L', 'U', 'R'};

  const auto is_edge = [](const vector<vector<char>> &board, int i, int j) {
    return i == 0 || j == 0 || i == (board.size() - 1) ||
           j == (board[0].size() - 1);
  };

  vector<vector<int>> back_trace(n, vector<int>(m, -1));

  while (!q.empty()) {
    const auto curr = q.front();
    auto prev_i = curr[0];
    auto prev_j = curr[1];
    q.pop();
    // Prune the space

    if (board[prev_i][prev_j] == 'A' && is_edge(board, prev_i, prev_j)) {
      std::cout << "YES" << std::endl;
      auto dir = back_trace[prev_i][prev_j];
      int x = prev_i;
      int y = prev_j;
      string path;
      while (dir != -1) {

        path.push_back(dirs[dir]);
        x -= dx[dir];
        y -= dy[dir];
        dir = back_trace[x][y];
      }

      reverse(begin(path), end(path));
      std::cout << path.size() << std::endl;
      std::cout << path;
      return;
    }

    for (int i = 0; i < 4; ++i) {
      auto x = curr[0] + dx[i];
      auto y = curr[1] + dy[i];

      if (x >= 0 && x < n && y >= 0 && y < m && board[x][y] == '.') {
        board[x][y] = board[prev_i][prev_j];
        // FOR VISUALIZATION
        // print_board(board, n, m);

        if (board[x][y] == 'A') {
          back_trace[x][y] = i;
        }
        q.push({x, y});
      }
    }
  }

  cout << "NO" << endl;
  return;
}

int main() {
  int n = 0;
  int m = 0;
  cin >> n;
  cin >> m;
  vector<vector<char>> board(n, vector<char>(m, '-'));

  for (int i = 0; i < n; ++i) {
    std::string s;
    cin >> s;

    for (int j = 0; j < m; ++j) {
      board[i][j] = s[j];
    }
  }

  // print_board(board, n, m);
  solve(board, n, m);
  return 0;
}