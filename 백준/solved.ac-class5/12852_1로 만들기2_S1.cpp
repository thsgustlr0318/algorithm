#include <iostream>
using namespace std;
int dp[1000001];
int main()
{
	ios_base::sync_with_stdio(false), cout.tie(NULL);
	int n;
	cin >> n;
	dp[1] = 0;
	//1 ~ n까지 최소 횟수 구하기
	for (int idx = 1; idx <= n; idx++) {
		if (idx * 3 <= n && (!dp[idx * 3] || dp[idx * 3] - 1 > dp[idx]))
			dp[idx * 3] = dp[idx] + 1;
		if (idx * 2 <= n && (!dp[idx * 2] || dp[idx * 2] - 1 > dp[idx]))
			dp[idx * 2] = dp[idx] + 1;
		if (idx + 1 <= n && (!dp[idx + 1] || dp[idx + 1] - 1 > dp[idx]))
			dp[idx + 1] = dp[idx] + 1;
	}
	cout << dp[n] << "\n" << n << " ";
	//top-down으로 dp[n]부터 1씩 줄어들면서, 3, 2로 나누어 떨어지거나 1을 뺀 다음의 경우 탐색
	for (int idx = n - 1, cnt = dp[n] - 1, prev = n; idx >= 1; idx--) {
		if (cnt == dp[idx] && (idx * 3 == prev || idx * 2 == prev || idx + 1 == prev)) {
			cout << idx << " ";
			cnt--;
			prev = idx;
		}
	}
}