#include <iostream>
#include <vector>
using namespace std;
bool dp[2001][2001];
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int n, m;
	cin >> n;
	vector<int> arr(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	//dp설정
	for (int i = 1; i <= n; i++)
		dp[i][i] = true;
	for (int i = 2; i <= n; i++)
		if (arr[i - 1] == arr[i])
			dp[i - 1][i] = true;
	for (int term = 2; term < n; term++) {
		for (int idx = 1; idx <= n - term; idx++) {
			if (arr[idx] == arr[idx + term] && dp[idx + 1][idx + term - 1])
				dp[idx][idx + term] = true;
		}
	}
	//팰린드롬 확인
	cin >> m;
	while (m--) {
		int a, b;
		cin >> a >> b;
		if (dp[a][b])
			cout << "1\n";
		else
			cout << "0\n";
	}
}