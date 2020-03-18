#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int arr[2][100001], dp[2][100001];
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int j = 0; j < 2; j++)
			for (int i = 1; i <= n; i++)
				cin >> arr[j][i];
		dp[0][1] = arr[0][1], dp[1][1] = arr[1][1];
		for (int i = 2; i <= n; i++) {
			dp[0][i] = max(dp[1][i - 2], dp[1][i - 1]) + arr[0][i];
			dp[1][i] = max(dp[0][i - 2], dp[0][i - 1]) + arr[1][i];
		}
		cout << max(dp[0][n], dp[1][n]) << "\n";
	}
}