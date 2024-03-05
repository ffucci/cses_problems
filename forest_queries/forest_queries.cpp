#include <iostream>
#include <iterator>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

using ui = unsigned int;
using ll = long long;

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int m, nq;
  cin >> m >> nq;
  vector<vector<int>> pref(m + 1, vector<int>(m + 1, 0));

  for (int i = 1; i <= m; ++i)
  {
    string row;
    cin >> row;
    for (int j = 1; j <= m; ++j)
    {
      if (row[j - 1] == '*')
      {
        pref[i][j] = 1;
      }
    }
  }

  vector<vector<int>> queries(nq, vector<int>(4, 0));
  for (int i = 0; i < nq; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      cin >> queries[i][j];
    }
  }

  for (int i = 1; i <= m; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      pref[i][j] = pref[i][j] - pref[i - 1][j - 1] + pref[i - 1][j] + pref[i][j - 1];
    }
  }

  constexpr bool ENABLE_DEBUG{false};
  if constexpr (ENABLE_DEBUG)
  {
    for (int i = 0; i <= m; ++i)
    {
      for (int j = 0; j <= m; ++j)
      {
        cout << pref[i][j] << " ";
      }
      cout << endl;
    }
  }

  for (auto q : queries)
  {
    auto y1 = q[0] - 1;
    auto x1 = q[1] - 1;
    auto y2 = q[2];
    auto x2 = q[3];
    auto val = pref[y2][x2] + pref[y1][x1] - pref[y1][x2] - pref[y2][x1];
    cout << val << endl;
  }
  return 0;
}