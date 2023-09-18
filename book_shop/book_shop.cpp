#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int solveRec(const vector<int> &prices, const vector<int> &pages, int i, int amount)
{
    if (i >= prices.size())
    {
        return 0;
    }

    int op1 = 0;
    if (amount - prices[i] >= 0)
    {
        op1 = pages[i] + solveRec(prices, pages, i + 1, amount - prices[i]);
    }

    return max(solveRec(prices, pages, i + 1, amount), op1);
}

int solveDP(const vector<int> &prices, const vector<int> &pages, int x)
{
    assert(prices.size() == pages.size());
    const auto n = prices.size();
    vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));

    for (int i = n - 1; i >= 0; --i)
    {
        for (int c = 0; c <= x; ++c)
        {
            dp[i][c] = dp[i + 1][c];
            if (c - prices[i] >= 0)
            {
                dp[i][c] = max(dp[i][c], pages[i] + dp[i + 1][c - prices[i]]);
            }
        }
    }

    return dp[0][x];
}

int main()
{
    int n = 0;
    int x = 0;
    cin >> n >> x;
    vector<int> prices(n, 0);
    vector<int> pages(n, 0);
    for (int i = 0; i < n; ++i)
    {
        cin >> prices[i];
    }

    for (int i = 0; i < n; ++i)
    {
        cin >> pages[i];
    }

    // const auto result = solveRec(prices, pages, 0, x);
    const auto result = solveDP(prices, pages, x);
    cout << result << endl;
    return 0;
}