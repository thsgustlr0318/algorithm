#include <iostream>
#include <algorithm>
#include <cstring>
#define MAXV 1e9
using namespace std;
int dp[1000][3], house[1000][3];
int main()
{
	int n, ans = 2e9;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 3; j++)
			cin >> house[i][j];
	for (int idx = 0; idx < 3; idx++) {
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < 3; i++) {
			if (i == idx)
				dp[0][i] = house[0][i];
			else
				dp[0][i] = MAXV;
		}
		for (int i = 1; i < n; i++) {
			dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + house[i][0];
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + house[i][1];
			dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + house[i][2];
		}
		for (int i = 0; i < 3; i++)
			if(i != idx)
				ans = min(ans, dp[n - 1][i]);
	}
	cout << ans;
}