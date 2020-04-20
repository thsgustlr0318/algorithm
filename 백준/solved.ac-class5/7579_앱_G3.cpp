#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int dp[10001];
int main()
{
	int n, m, maxsize = 0, ans = 0;
	cin >> n >> m;
	vector<int> byte(n), cost(n);
	for (int i = 0; i < n; i++)
		cin >> byte[i];
	for (int i = 0; i < n; i++) {
		cin >> cost[i];
		maxsize += cost[i];
	}
	//dp[i] = i만큼의 비용을 사용 가능할 때, 최대 메모리 크기
	//M바이트 확보하기 위한 최소 비용: dp[i]값이 M이상일 때의 i값
	//n개의 프로그램을 하나씩 살펴보면서(idx 0부터 시작), i비용일 때의 최대 메모리 값을 구함
	for (int idx = 0; idx < n; idx++) {
		for (int i = maxsize; i >= 0 && i - cost[idx] >= 0; i--) {
			dp[i] = max(dp[i], dp[i - cost[idx]] + byte[idx]);
		}
	}
	for (int i = 0; i <= maxsize; i++)
		if (dp[i] >= m) {
			ans = i;
			break;
		}
	cout << ans;
}