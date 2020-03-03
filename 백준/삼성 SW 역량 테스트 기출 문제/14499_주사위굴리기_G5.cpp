#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int board[20][20], y, x, k, n, m;
	cin >> n >> m >> y >> x >> k;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> board[i][j];
	int dice[4][3] = { {-1, 0, -1}, {0, 0, 0}, {-1, 0, -1}, {-1 ,0, -1} };

	for (int i = 0; i < k; i++) {
		int com;
		cin >> com;
		if (com == 1) {
			if (x + 1 >= m)
				continue;
			swap(dice[1][0], dice[1][1]);
			swap(dice[1][1], dice[3][1]);
			swap(dice[1][1], dice[1][2]);
			x++;
		}
		else if (com == 2) {
			if (x - 1 < 0)
				continue;
			swap(dice[1][0], dice[1][1]);
			swap(dice[1][0], dice[1][2]);
			swap(dice[1][0], dice[3][1]);
			x--;
		}
		else if (com == 3) {
			if (y - 1 < 0)
				continue;
			swap(dice[3][1], dice[2][1]);
			swap(dice[2][1], dice[1][1]);
			swap(dice[1][1], dice[0][1]);
			y--;
		}
		else {
			if (y + 1 >= n)
				continue;
			swap(dice[0][1], dice[1][1]);
			swap(dice[1][1], dice[2][1]);
			swap(dice[2][1], dice[3][1]);
			y++;
		}
		if (board[y][x] == 0) {
			board[y][x] = dice[1][1];
		}
		else {
			dice[1][1] = board[y][x];
			board[y][x] = 0;
		}
		cout << dice[3][1] << endl;
	}
}