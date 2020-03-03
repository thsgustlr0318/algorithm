#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int n, t[20], p[20];
	int dp[20] = { 0 };
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> t[i] >> p[i];
	for (int i = 1; i <= n; i++) {
		dp[i + t[i] - 1] = max(dp[i + t[i] - 1], dp[i - 1] + p[i]);
		dp[i] = max(dp[i], dp[i - 1]);
	}
	cout << dp[n];
}