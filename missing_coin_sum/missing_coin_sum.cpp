#include <array>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

using ll = long long int;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N = 0;
  cin >> N;
  vector<int> coins(N, 0);
  for (int i = 0; i < N; ++i) {
    cin >> coins[i];
  }

  std::sort(begin(coins), end(coins));

  ll curr_sum = 1;
  for (int i = 0; i < N; ++i) {
    if (coins[i] > curr_sum) {
      break;
    }

    curr_sum += coins[i];
  }

  cout << curr_sum << endl;
  return 0;
}