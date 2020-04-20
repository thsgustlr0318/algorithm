#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 2147483647
using namespace std;
int dp[501][501];
int main()
{
	int n;
	cin >> n;
	vector<pair<int, int>> v(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> v[i].first >> v[i].second;
	//dp[i][j] = i ~ j행렬까지의 곱 중 최솟값
	//i ~ j 사이에 임의의 k값을 설정해놓고, [ (i ~ k)까지 최솟값 + (k+1 ~ j)까지 최솟값 + 두 행렬의 연산값 ] 중 최소를 찾음
	for (int i = n - 1; i > 0; i--) {
		for (int j = i + 1; j <= n; j++) {
			dp[i][j] = MAX;
			for (int k = i; k < j; k++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + v[i].first * v[k].second * v[j].second);
			}
		}
	}
	cout << dp[1][n];
}