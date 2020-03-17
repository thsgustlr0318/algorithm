#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, island_count, ans = 0;
int map[10][10], visit[10][10], bridge[7][7];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
vector<pair<int, int>> island_pos[7];
//섬마다 번호 붙이기
//island_pos[i] = i번 섬을 구성하는 (y, x)좌표 모음
void findIsland(int y, int x)
{
	queue<pair<int, int>> q;
	q.push({ y, x });
	island_count++;
	map[y][x] = island_count;
	visit[y][x] = true;
	island_pos[island_count].push_back({ y,x });
	while (!q.empty()) {
		int cy = q.front().first, cx = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = cy + moveDir[i][0], nx = cx + moveDir[i][1];
			if (ny < 0 || nx < 0 || ny >= n || nx >= m || !map[ny][nx] || visit[ny][nx]) continue;
			visit[ny][nx] = true;
			map[ny][nx] = map[cy][cx];
			q.push({ ny, nx });
			island_pos[island_count].push_back({ ny,nx });
		}
	}
}
//각 섬에서 만들 수 있는 다리길이 구하기
//bridge[i][j] = i섬에서 j섬에 놓을 수 있는 최소 다리길이
//다리 건설 불가능할경우 0
void findBridge(int src)
{
	vector<int> check(island_count + 1, 2e9);
	for (int idx = 0; idx < island_pos[src].size(); idx++) {
		int cy = island_pos[src][idx].first, cx = island_pos[src][idx].second;
		for (int i = 0; i < 4; i++) {
			int cnt = 0;
			int ny = cy, nx = cx;
			while (1) {
				ny = ny + moveDir[i][0], nx = nx + moveDir[i][1];
				cnt++;
				if (ny < 0 || nx < 0 || ny >= n || nx >= m || map[ny][nx] == src) break;
				if (map[ny][nx] != 0 && map[ny][nx] != src) {
					//다리 길이가 2 이상이어야함
					if (cnt != 2)
						check[map[ny][nx]] = min(check[map[ny][nx]], cnt - 1);
					break;
				}
			}
		}
	}
	for (int i = 1; i <= island_count; i++) {
		if (check[i] != 2e9)
			bridge[src][i] = bridge[i][src] = check[i];
	}
}
int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> map[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (map[i][j] == 1 && !visit[i][j])
				findIsland(i, j);
	for (int i = 1; i <= island_count; i++)
		findBridge(i);
	vector<int> v;
	v.push_back(1);
	for (int i = 1; i < island_count; i++) {
		int minv = 2e9, connect;
		for (auto it = v.begin(); it != v.end(); it++) {
			for (int k = 1; k <= island_count; k++) {
				if (*it != k && bridge[*it][k] != 0 && find(v.begin(), v.end(), k) == v.end()) {
					if (minv > bridge[*it][k]) {
						minv = bridge[*it][k];
						connect = k;
					}
				}
			}
		}
		if (minv == 2e9) {
			ans = -1;
			break;
		}
		v.push_back(connect);
		ans += minv;
	}
	cout << ans;
}