#include <iostream>
using namespace std;
#define MOD 1000000007
long long dp[101][101][101];
int main()
{
	int n, l, r;
	cin >> n >> l >> r;
	dp[1][1][1] = dp[2][2][1] = dp[2][1][2] = 1;
	for (int i = 3; i <= n; i++) {
		for (int j = 1; j <= l; j++) {
			for (int k = 1; k <= r; k++) {
				dp[i][j][k] = dp[i - 1][j][k] * (i - 2) + dp[i - 1][j - 1][k] + dp[i - 1][j][k - 1];
				dp[i][j][k] %= MOD;
			}
		}
	}
	cout << dp[n][l][r];
}
//건물이 가장 높은것부터 작은 순서대로 하나씩 놓는다고 생각했을 때
//dp[n][l][r] = n개의 건물이 있을 때, 왼쪽에서 l개, 오른쪽에서 r개의 건물이 보이는 경우의 수
//가장 작은 건물을 맨 왼쪽에 놓았을 경우, l값 1씩 증가
//가장 작은 건물을 맨 오른쪽에 놓았을 경우, r값 1씩 증가
//중간에 놓았을 경우, l, r값 그대로