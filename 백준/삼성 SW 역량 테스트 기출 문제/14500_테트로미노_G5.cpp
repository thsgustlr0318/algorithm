#include <iostream>
#include <algorithm>
using namespace std;

bool visit[500][500];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, 1} };
int n, m, result;
int board[500][500];

int dfs(int y, int x, int idx)
{
	if (idx == 4) {
		return board[y][x];
	}
	int ans = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + moveDir[i][0];
		int nx = x + moveDir[i][1];
		if (0 > ny || 0 > nx || ny >= n || nx >= m || visit[ny][nx] == true)
			continue;

		visit[ny][nx] = true;
		ans = max(ans, board[y][x] + dfs(ny, nx, idx + 1));
		visit[ny][nx] = false;
	}
	return ans;
}
int f(int y, int x)
{
	int ans = 0;
	if (y + 1 < n && x + 2 < m) {
		ans = max(ans, board[y][x] + board[y][x + 1] + board[y][x + 2] + board[y + 1][x + 1]);
		ans = max(ans, board[y + 1][x] + board[y + 1][x + 1] + board[y + 1][x + 2] + board[y][x + 1]);
	}
	if (y + 2 < n && x + 1 < m) {
		ans = max(ans, board[y][x] + board[y + 1][x] + board[y + 2][x] + board[y + 1][x + 1]);
		ans = max(ans, board[y][x + 1] + board[y + 1][x + 1] + board[y + 2][x + 1] + board[y + 1][x]);
	}
	return ans;
}

	
int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> board[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			visit[i][j] = true;
			result = max(result, dfs(i, j, 1));
			result = max(result, f(i, j));
			visit[i][j] = false;
		}
	cout << result;
}