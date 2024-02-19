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
      shigh_ += element;
    }
    else
    {
      low_.insert(element);
      slow_ += element;
    }

    if (low_.size() > high_.size() + 1)
    {
      auto fin = low_.rbegin();
      auto value = *fin;
      high_.insert(*fin);
      shigh_ += value;
      low_.erase(std::prev(low_.end()));
      slow_ -= value;
    }

    if (low_.size() < high_.size())
    {
      auto beg = high_.begin();
      auto val = *beg;
      low_.insert(*beg);
      slow_ += val;
      high_.erase(beg);
      shigh_ -= val;
    }
  }

  int median() const noexcept
  {
    if (k_ % 2 == 0)
    {
      return 0;
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
      auto val = *lower_itr;
      low_.erase(lower_itr);
      slow_ -= val;
      // now high size greater or equal
      if (low_.size() < high_.size())
      {
        auto first_high = high_.begin();
        auto first_high_val = *first_high;
        low_.insert(*first_high);
        slow_ += first_high_val;
        high_.erase(first_high);
        shigh_ -= first_high_val;
      }
      return;
    }

    auto higher_itr = high_.find(element);
    if (higher_itr != high_.end())
    {
      auto higher_val = *higher_itr;
      high_.erase(higher_itr);
      shigh_ -= higher_val;

      // now high size greater or equal
      if (low_.size() > high_.size() + 1)
      {
        auto last_low = std::prev(low_.end());
        auto last_low_val = *last_low;
        high_.insert(*last_low);
        shigh_ += last_low_val;
        low_.erase(last_low);
        slow_ -= last_low_val;
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

  ll cost() const noexcept
  {
    // cout << "shigh: " << shigh_ << " slow: " << slow_ << endl;
    return shigh_ - slow_ + median();
  }

private:
  multiset<int> low_;
  multiset<int> high_;
  int k_{0};

  ll slow_{0};
  ll shigh_{0};
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
      cout << sw.cost() << " ";
      sw.remove(elements[i - k + 1]);
    }
  }
  cout << endl;
  return 0;
}