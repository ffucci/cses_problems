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

  vector<pll> events(N);

  for (int i = 0; i < N; ++i)
  {
    ll start = 0;
    ll end = 0;
    cin >> start >> end;
    events[i].first = start;
    events[i].second = end;
  }

  ll best = 1;
  ll r = -1;
  sort(begin(events), end(events), [](const pll &left, const pll &right)
       { return left.second < right.second; });

  ll current = 0;
  int cnt = 0;
  ll curr_end_event = -1;
  for (int i = 0; i < N; ++i)
  {
    // The start time of the current event is greater then the sorted end time
    if (events[i].first >= curr_end_event)
    {
      // We just go to the next event greater than the current end
      // time because the events are sorted by end time.
      cnt++;
      curr_end_event = events[i].second;
    }
  }

  cout << cnt << endl;
  return 0;
}