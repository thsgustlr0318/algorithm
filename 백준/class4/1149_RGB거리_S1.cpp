#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
	int n;
	cin >> n;
	int cost[1000][3];
	int dp[1000][3];
	fill(&dp[0][0], &dp[999][2], 0);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 3; j++)
			cin >> cost[i][j];
	dp[0][0] = cost[0][0], dp[0][1] = cost[0][1], dp[0][2] = cost[0][2];
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			dp[i][j] = cost[i][j] + min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
		}
	}
	cout << min(dp[n - 1][0], min(dp[n - 1][1], dp[n - 1][2]));
}