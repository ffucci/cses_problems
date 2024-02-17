#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

using ll = long long int;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N = 0;
  cin >> N;

  vector<ll> v(N, 0);

  for (int i = 0; i < N; ++i)
  {
    cin >> v[i];
  }

  ll best = 1;
  ll r = -1;
  set<ll> window;
  for (int l = 0; l < N; ++l)
  {
    // Keep adding to the set up until we already had an element inserted in
    while (r < N - 1 && window.count(v[r + 1]) == 0)
    {
      window.insert(v[++r]);
    }
    best = max(best, r - l + 1);
    window.erase(v[l]);
  }
  cout << best << endl;
  return 0;
}