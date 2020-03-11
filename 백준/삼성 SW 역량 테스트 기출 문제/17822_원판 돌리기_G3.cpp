#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
struct pos {
	int disk, cnt;
};
int n, m, t, ans, total;
int board[50][50];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
bool visit[50][50];
queue<pos> command;
int main()
{
	cin >> n >> m >> t;
	total = n * m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> board[i][j];
	for (int i = 0; i < t; i++) {
		int x, d, k;
		cin >> x >> d >> k;
		//원판 돌리는 방향 고정
		d == 0 ? k %= m : k = m - k % m;
		command.push({ x, k });
	}
	while (!command.empty()) {
		pos cur = command.front();
		command.pop();
		//원판 회전
		for (int idx = cur.disk; idx <= n; idx += cur.disk)
			rotate(board[idx - 1], board[idx - 1] + m - cur.cnt, board[idx - 1] + m);
		bool flag = false;
		memset(visit, 0, sizeof(visit));		
		//같은 수 지우기
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				if (board[i][j] == 0 || visit[i][j]) continue;
				visit[i][j] = true;
				queue<pair<int, int>> q, q2;
				q.push(make_pair(i, j));
				while (!q.empty()) {
					int y = q.front().first, x = q.front().second;
					q.pop();
					for (int k = 0; k < 4; k++) {
						int ny = y + moveDir[k][0], nx = x + moveDir[k][1];
						if (ny < 0 || ny >= n) continue;
						else if (nx < 0) nx = m - 1;
						else if (nx >= m) nx = 0;
						if (visit[ny][nx] || board[ny][nx] == 0 || board[ny][nx] != board[y][x]) continue;
						q.push(make_pair(ny, nx));
						q2.push(make_pair(ny, nx));
						visit[ny][nx] = true;
						flag = true;
						total--;
					}
				}
				if (q2.empty()) continue;
				board[i][j] = 0;
				total--;
				while (!q2.empty()) {
					int y = q2.front().first, x = q2.front().second;
					q2.pop();
					board[y][x] = 0;
				}
			}
		//인접한 수가 없을 경우
		if (!flag) {
			int temp = 0;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					temp += board[i][j];
			double mid = (double)temp / total;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++) {
					if (board[i][j] != 0) {
						if (board[i][j] > mid) board[i][j]--;
						else if (board[i][j] < mid) board[i][j]++;
					}
				}
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans += board[i][j];
	cout << ans;
}