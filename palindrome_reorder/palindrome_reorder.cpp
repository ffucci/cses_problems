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

  std::string s;
  cin >> s;

  unordered_map<char, long long int> freq;

  for (auto &c : s)
  {
    freq[c]++;
  }

  int cnt_odd = 0;

  for (auto [k, v] : freq)
  {
    if (v % 2 == 1)
    {
      cnt_odd++;
    }

    if (cnt_odd > 1)
    {
      cout << "NO SOLUTION" << endl;
      return 0;
    }
  }

  int l = 0;
  int r = s.size() - 1;

  int key_mod_1 = -1;
  for (auto [k, v] : freq)
  {
    if (v % 2 == 1)
    {
      key_mod_1 = k;
    }
    else
    {
      int num_copies = v;
      while (num_copies > 0)
      {
        s[l] = k;
        s[r] = k;
        l++;
        r--;
        num_copies -= 2;
      }
    }
  }

  while (l <= r && freq[key_mod_1] != 0)
  {
    s[l] = key_mod_1;
    s[r] = key_mod_1;
    l++;
    r--;
    freq[key_mod_1]--;
  }

  cout << s << endl;
  return 0;
}