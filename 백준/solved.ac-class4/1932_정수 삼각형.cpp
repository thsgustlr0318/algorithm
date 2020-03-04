#include <iostream>
#include <algorithm>
using namespace std;

int arr[500][500];
int dp[500][501];
int main()
{
	int n, ans = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i + 1; j++)
			cin >> arr[i][j];
	dp[0][0] = arr[0][0];
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < i + 1; j++) {
			dp[i][j] = max(dp[i - 1][j - 1] + arr[i][j], dp[i - 1][j] + arr[i][j]);
		}
		dp[i][0] = dp[i - 1][0] + arr[i][0];
	}
	for (int i = 0; i < n; i++)
		ans = max(ans, dp[n - 1][i]);
	cout << ans;
}