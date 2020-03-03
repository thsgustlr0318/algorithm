#include <iostream>
using namespace std;

int moveDir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
int board[50][50];
int n, m, y, x, d, ans;
void dfs(int y, int x, int d)
{
	if (board[y][x] == 0) {
		ans++;
		board[y][x] = 2;
	}
	for (int i = 0; i < 4; i++) {
		d = (d + 3) % 4;
		int ny = y + moveDir[d][0];
		int nx = x + moveDir[d][1];
		if (ny < 1 || nx < 1 || ny >= n - 1 || nx >= m - 1 || board[ny][nx] == 1 || board[ny][nx] == 2)
			continue;
		dfs(ny, nx, d);
	}
	if (board[y + moveDir[(d + 2) % 4][0]][x + moveDir[(d + 2) % 4][1]] != 1)
		dfs(y + moveDir[(d + 2) % 4][0], x + moveDir[(d + 2) % 4][1], d);
	else {
		cout << ans;
		exit(0);
	}		
}

int main()
{	
	cin >> n >> m >> y >> x >> d;	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> board[i][j];
	dfs(y, x, d);
}