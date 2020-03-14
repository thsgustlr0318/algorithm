#include <iostream>
using namespace std;
#define GARO 1
#define SERO 2
#define DEGAK 3
int arr[17][17];
int n, ans = 0;
void dfs(int y, int x, int status)
{
	if (y >= n || x >= n || arr[y][x] == 1) return;
	if (y == n - 1 && x == n - 1) {
		ans++;
		return;
	}
	if (status == GARO)
		dfs(y, x + 1, GARO);
	else if (status == SERO)
		dfs(y + 1, x, SERO);
	else {
		dfs(y, x + 1, GARO);
		dfs(y + 1, x, SERO);
	}
	if (arr[y + 1][x] == 0 && arr[y][x + 1] == 0)
		dfs(y + 1, x + 1, DEGAK);
}
int main()
{	
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];
	dfs(0, 1, GARO);
	cout << ans;
}