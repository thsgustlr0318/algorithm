#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n, k;
int dp[101][100001];
int main()
{
	cin >> n >> k;
	vector<pair<int, int>> bag;
	bag.reserve(n);
	for (int i = 0; i < n; i++) {
		int w, v;
		cin >> w >> v;
		bag.push_back(make_pair(w, v));
	}
	for (int i = bag[0].first; i <= k; i++)
		dp[0][i] = bag[0].second;
	for (int i = 1; i < n; i++)
		for (int j = 1; j <= k; j++) {
			if (bag[i].first <= j) {
				dp[i][j] = max(dp[i - 1][j], bag[i].second + dp[i - 1][j - bag[i].first]);
			}
			else
				dp[i][j] = dp[i - 1][j];
		}
	cout << dp[n - 1][k];
}