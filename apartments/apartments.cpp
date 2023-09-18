#include <algorithm>
#include <iostream>
#include <ranges>
#include <set>
#include <vector>

using namespace std;

int main() {
  int n = 0;
  int m = 0;
  int k = 0;
  cin >> n >> m >> k;
  vector<int> applicants(n, 0);
  vector<int> sizes(m, 0);

  for (int i = 0; i < n; ++i) {
    cin >> applicants[i];
  }

  for (int i = 0; i < m; ++i) {
    cin >> sizes[i];
  }

  std::ranges::sort(applicants);
  std::ranges::sort(sizes);

  size_t count = 0;

  int i = 0, j = 0;
  while (i < n && j < m) {
    if (abs(applicants[i] - sizes[j]) <= k) {
      ++i;
      ++j;
      ++count;
    } else {
      // If the desired apartment size of the applicant is too big,
      // move the apartment pointer to the right to find a bigger one
      if (applicants[i] - sizes[j] > k) {
        ++j;
      }
      // If the desired apartment size is too small,
      // skip that applicant and move to the next person
      else {
        ++i;
      }
    }
  }
  cout << count << endl;
  return 0;
}