#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

using ll = long long int;

class SlidingWindowMedian
{
public:
  explicit SlidingWindowMedian(int k) : k_(k) {}

  void add(int element)
  {
    if (!low_.empty() && *low_.rbegin() < element)
    {
      high_.insert(element);
    }
    else
    {
      low_.insert(element);
    }

    if (low_.size() > high_.size() + 1)
    {
      auto fin = low_.rbegin();
      high_.insert(*fin);
      low_.erase(std::prev(low_.end()));
    }

    if (low_.size() < high_.size())
    {
      auto beg = high_.begin();
      low_.insert(*beg);
      high_.erase(beg);
    }
  }

  int median()
  {
    if (k_ % 2 == 0)
    {
      auto end_first = *(std::prev(low_.end()));
      auto beg_second = *high_.begin();
      return min(beg_second, end_first);
    }
    else
    {
      return *std::prev(low_.end());
    }
  }

  void remove(int element)
  {
    auto lower_itr = low_.find(element);
    if (lower_itr != low_.end())
    {
      low_.erase(lower_itr);
      // now high size greater or equal
      if (low_.size() < high_.size())
      {
        auto first_high = high_.begin();
        low_.insert(*first_high);
        high_.erase(first_high);
      }
      return;
    }

    auto higher_itr = high_.find(element);
    if (higher_itr != high_.end())
    {
      high_.erase(higher_itr);
      // now high size greater or equal
      if (low_.size() > high_.size() + 1)
      {
        auto last_low = std::prev(low_.end());
        high_.insert(*last_low);
        low_.erase(last_low);
      }
    }
  }

  void print()
  {
    cout << "\nlow: ";
    for (auto &el : low_)
    {
      cout << el << " ";
    }
    cout << endl;

    cout << "high: ";
    for (auto &el : high_)
    {
      cout << el << " ";
    }

    cout << endl;
    cout << "##########" << endl;
  }

private:
  multiset<int> low_;
  multiset<int> high_;
  int k_;
};

int main()
{
  int n, k;
  cin >> n >> k;
  SlidingWindowMedian sw(k);
  vector<int> elements(n, 0);
  for (int i = 0; i < n; ++i)
  {
    ll var;
    cin >> var;
    elements[i] = var;
  }

  for (int i = 0; i < n; ++i)
  {
    sw.add(elements[i]);
    if (i >= k - 1)
    {
      cout << sw.median() << " ";
      sw.remove(elements[i - k + 1]);
    }
  }
  cout << endl;
  return 0;
}