#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct pos {
	int z, y, x;
};
int mapInput[5][5][5], mapFind[5][5][5];
int use[5], visit[5][5][5];
int ans = 2e9;
int moveDir[6][3] = { {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1} };
//탐색 가능한지 확인
bool check(int cnt, int idx)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (mapFind[cnt - 1][i][j] == 1 && mapInput[idx][i][j] == 1 && mapFind[cnt - 1][i][j] == mapInput[idx][i][j])
				return true;
	return false;
}
//mapInput[idx]를 시계방향으로 회전
void rotateArr(int idx)
{
	int temp[5][5];
	memcpy(temp, mapInput[idx], sizeof(temp));
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			mapInput[idx][i][j] = temp[4 - j][i];
}
//완성된 미로 탐색
int bfs()
{
	queue<pos> q;
	q.push({ 0, 0, 0 });
	visit[0][0][0] = true;
	while (!q.empty()) {
		int z = q.front().z, y = q.front().y, x = q.front().x;
		q.pop();
		if (z == 4 && y == 4 && x == 4) {
			return visit[4][4][4] - 1;
		}
		for (int i = 0; i < 6; i++) {
			int nz = z + moveDir[i][2], ny = y + moveDir[i][0], nx = x + moveDir[i][1];
			if (nz < 0 || ny < 0 || nx < 0 || ny >= 5 || nx >= 5 || nz >= 5 || visit[nz][ny][nx] || !mapFind[nz][ny][nx]) continue;
			visit[nz][ny][nx] = visit[z][y][x] + 1;
			q.push({ nz, ny, nx });
		}
	}
	return 2e9;
}
//미로 선택
void dfs(int cnt)
{
	if (cnt == 5) {
		//미로 찾기
		memset(visit, 0, sizeof(visit));
		ans = min(ans, bfs());
		return;
	}
	for (int i = 0; i < 5; i++) {
		if (use[i]) continue;
		//돌려가면서 미로 탐색
		for (int j = 0; j < 4; j++) {
			if ((cnt == 0 && mapInput[i][0][0] == 1) || (0 < cnt && cnt < 4 && check(cnt, i)) || cnt == 4 && mapInput[i][4][4] == 1) {
				use[i] = true;
				memcpy(mapFind[cnt], mapInput[i], sizeof(mapInput[i]));
				dfs(cnt + 1);
				use[i] = false;
			}
			rotateArr(i);
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				cin >> mapInput[i][j][k];
	dfs(0);
	if (ans == 2e9) ans = -1;
	cout << ans;
}