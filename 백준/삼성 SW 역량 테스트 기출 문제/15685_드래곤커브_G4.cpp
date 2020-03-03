#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, board[101][101];
int moveDir[4][2] = { {0, 1}, {-1, 0 }, {0, -1}, {1, 0} };
void dfs(int x, int y, int d, int g)
{
	vector<int> v;
	int ny = y + moveDir[d][0];
	int nx = x + moveDir[d][1];
	v.push_back(d);
	board[y][x] = true;
	board[ny][nx] = true;
	y = ny, x = nx;

	while (g--) {
		for (int i = v.size() - 1; i >= 0; i--) {
			int temp = (v[i] + 1) % 4;
			ny = y + moveDir[temp][0];
			nx = x + moveDir[temp][1];
			if (0 <= ny && ny <= 100 && 0 <= nx && nx <= 100)
				board[ny][nx] = true;
			v.push_back(temp);
			y = ny, x = nx;
		}
	}
}
int main()
{
	int ans = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		dfs(x, y, d, g);
	}
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++) {
			if (board[i][j] && board[i + 1][j] && board[i][j + 1] && board[i + 1][j + 1])
				ans++;
		}
	cout << ans;
}