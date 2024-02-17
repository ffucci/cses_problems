#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

using ll = long long int;
using pll = std::pair<ll, ll>;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N = 0;
  cin >> N;

  vector<pll> v(N);

  for (int i = 0; i < N; ++i)
  {
    ll start = 0;
    ll end = 0;
    cin >> start >> end;
    v[i].first = start;
    v[i].second = end;
  }

  ll best = 1;
  ll r = -1;
  sort(begin(v), end(v));

  ll current = 0;
  int cnt = 1;
  for (int i = 0; i < N - 1; ++i)
  {
    if (v[i].second < v[i + 1].first)
    {
      cnt++;
    }
  }

  cout << cnt << endl;
  return 0;
}