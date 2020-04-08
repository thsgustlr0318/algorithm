#include <iostream>
#include <algorithm>
using namespace std;
int board[20][20];
int n, ans = 2e9;
void dfs(int cnt)
{
	//모든 행 뒤집었으면, 각 열에서 동전 뒤집을지 안뒤집을지 결정
	if (cnt == n) {
		//total = 동전 뒷면의 갯수
		int total = 0;
		for (int i = 0; i < n; i++) {
			int temp = 0;
			//temp = 각 열의 뒷면 갯수
			for (int j = 0; j < n; j++)
				if (board[j][i] == 1) temp++;
			//뒷면의 갯수가 n/2보다 크면, 뒤집음
			if (temp > n / 2) total += n - temp;
			else total += temp;
		}
		ans = min(ans, total);
		return;
	}
	//cnt행 동전 뒤집지 않고 탐색
	dfs(cnt + 1);
	//cnt행 동전 뒤집고 탐색
	for (int i = 0; i < n; i++)
		board[cnt][i] = -board[cnt][i];
	dfs(cnt + 1);
}
int main()
{	
	char c;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> c;
			if (c == 'T') board[i][j] = 1;
			else board[i][j] = -1;
		}
	}
	dfs(0);
	cout << ans;
}
//brute force로 확인
//열을 확인할 땐, 뒷면 갯수 세어서 확인