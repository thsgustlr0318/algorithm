#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, ans;
int board[20][20];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
bool visit[20][20], blankvisit[400];
vector<pair<int, int>> blank, enemy;
//죽일 수 있는 상대 돌의 최대 갯수 구하기
int bfs()
{
	memset(visit, false, sizeof(visit));
	int total = 0;
	//모든 상대돌의 좌표로부터 탐색 시작
	for (int i = 0; i < (int)enemy.size(); i++) {
		//이미 탐색된 경우, continue
		if (visit[enemy[i].first][enemy[i].second]) continue;
		queue<pair<int, int>> q;
		q.push(enemy[i]);
		visit[enemy[i].first][enemy[i].second] = true;
		int temp = 1;
		bool flag = false;
		while (!q.empty()) {
			int y = q.front().first, x = q.front().second;
			q.pop();
			for (int j = 0; j < 4; j++) {
				int ny = y + moveDir[j][0], nx = x + moveDir[j][1];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m || visit[ny][nx] || board[ny][nx] == 1) continue;
				//주변에 빈 칸이 있는 경우, 돌을 죽이지 못함
				if (board[ny][nx] == 0) flag = true;
				q.push({ ny, nx });
				visit[ny][nx] = true;
				temp++;
			}
		}
		//돌을 못죽인 경우
		if (!flag) total += temp;
	}
	return total;
}
void dfs(int cnt, int idx)
{
	if (cnt == 2) {		
		ans = max(ans, bfs());
		return;
	}
	for (int i = idx; i < (int)blank.size(); i++) {
		if (blankvisit[i]) continue;
		blankvisit[i] = true;
		board[blank[i].first][blank[i].second] = 1;
		dfs(cnt + 1, i + 1);
		board[blank[i].first][blank[i].second] = 0;
		blankvisit[i] = false;
	}
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
			if (board[i][j] == 0) blank.push_back({ i, j });
			if (board[i][j] == 2) enemy.push_back({ i, j });
		}
	dfs(0, 0);
	cout << ans;
}