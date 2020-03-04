#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int n, m, ans = 2e9;
int visit[2][1000][1000];
string arr[1000];
struct pos {
	int y, x;
	bool wall;
	pos(int a, int b, bool c) {
		y = a, x = b, wall = c;
	}
};
void bfs()
{
	queue<pos> q;
	q.push(pos(0, 0, false));
	visit[0][0][0] = 1;
	visit[1][0][0] = 1;
	while (!q.empty()) {
		pos cur = q.front();
		int y = cur.y, x = cur.x;
		q.pop();
		if (cur.y == n - 1 && cur.x == m - 1) {
			ans = min(ans, visit[cur.wall][y][x]);
			continue;
		}
		for (int i = 0; i < 4; i++) {
			int ny = y + moveDir[i][0], nx = x + moveDir[i][1];
			if (ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
			if (cur.wall) {
				if (arr[ny][nx] == 0 && !visit[cur.wall][ny][nx]) {
					visit[cur.wall][ny][nx] = visit[cur.wall][y][x] + 1;
					q.push(pos(ny, nx, cur.wall));
				}
			}
			else {
				if (arr[ny][nx] == 0 && !visit[cur.wall][ny][nx]) {
					visit[cur.wall][ny][nx] = visit[cur.wall][y][x] + 1;
					q.push(pos(ny, nx, cur.wall));
				}
				else if (arr[ny][nx] == 1 && !visit[cur.wall][ny][nx]) {
					visit[true][ny][nx] = visit[cur.wall][y][x] + 1;
					q.push(pos(ny, nx, true));
				}
			}
		}
	}
}
int main()
{	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		for (int j = 0; j < m; j++) 
			arr[i][j] -= '0';		
	}
	bfs();
	ans == 2e9 ? cout << "-1\n" : cout << ans;
}