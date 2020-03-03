#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

int board[20][20], n, ans;
void rotate()
{
	int temp[20][20];
	memcpy(temp, board, sizeof(temp));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			board[j][n - i - 1] = temp[i][j];
}
void move()
{
	queue<int> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] != 0)
				q.push(board[i][j]);
			board[i][j] = 0;
		}
		int index = 0;
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			if (board[i][index] == 0)
				board[i][index] = cur;
			else if (board[i][index] == cur)
				board[i][index++] *= 2;
			else
				board[i][++index] = cur;
		}
	}
}
void dfs(int idx)
{
	if (idx == 5) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				ans = max(ans, board[i][j]);
		return;
	}
	for (int i = 0; i < 4; i++) {
		int temp[20][20];
		rotate();
		memcpy(temp, board, sizeof(board));
		move();
		dfs(idx + 1);
		memcpy(board, temp, sizeof(board));
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> board[i][j];
	dfs(0);
	cout << ans;
}