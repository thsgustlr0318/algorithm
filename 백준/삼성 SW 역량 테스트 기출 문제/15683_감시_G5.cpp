#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

struct pos {
	int y, x, cctv;
	pos(int a, int b, int d) {
		y = a, x = b, cctv = d;
	}
	bool operator < (const pos &d) const {
		return this->cctv < d.cctv;
	}
};
int n, m, arr[8][8], ans;
int moveDir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
vector<pos> v;
void watch(int y, int x, int dir)
{
	int ny = y, nx = x;
	while (1) {
		ny += moveDir[dir][0];
		nx += moveDir[dir][1];
		if (ny < 0 || nx < 0 || ny >= n || nx >= m || arr[ny][nx] == 6)
			break;
		if (arr[ny][nx] == 0)
			arr[ny][nx] = -1;
	}
}

void dfs(int idx)
{
	if (idx == v.size()) {
		int result = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (arr[i][j] == 0)
					result++;
		ans = min(ans, result);
		return;
	}
	if (v[idx].cctv == 1) {
		for (int i = 0; i < 4; i++) {
			int temp[8][8];
			memcpy(temp, arr, sizeof(arr));
			watch(v[idx].y, v[idx].x, i);
			dfs(idx + 1);
			memcpy(arr, temp, sizeof(arr));
		}
	}
	else if (v[idx].cctv == 2) {
		for (int i = 0; i < 2; i++) {
			int temp[8][8];
			memcpy(temp, arr, sizeof(arr));
			watch(v[idx].y, v[idx].x, i);
			watch(v[idx].y, v[idx].x, i + 2);
			dfs(idx + 1);
			memcpy(arr, temp, sizeof(arr));
		}
	}
	else if (v[idx].cctv == 3) {
		for (int i = 0; i < 4; i++) {
			int temp[8][8];
			memcpy(temp, arr, sizeof(arr));
			watch(v[idx].y, v[idx].x, i % 4);
			watch(v[idx].y, v[idx].x, (i + 1) % 4);
			dfs(idx + 1);
			memcpy(arr, temp, sizeof(arr));
		}
	}
	else if (v[idx].cctv == 4) {
		for (int i = 0; i < 4; i++) {
			int temp[8][8];
			memcpy(temp, arr, sizeof(arr));
			watch(v[idx].y, v[idx].x, i % 4);
			watch(v[idx].y, v[idx].x, (i + 1) % 4);
			watch(v[idx].y, v[idx].x, (i + 2) % 4);
			dfs(idx + 1);
			memcpy(arr, temp, sizeof(arr));
		}
	}
	else {
		int temp[8][8];
		memcpy(temp, arr, sizeof(arr));
		watch(v[idx].y, v[idx].x, 0);
		watch(v[idx].y, v[idx].x, 1);
		watch(v[idx].y, v[idx].x, 2);
		watch(v[idx].y, v[idx].x, 3);
		dfs(idx + 1);
		memcpy(arr, temp, sizeof(arr));
	}
}
int main()
{
	cin >> n >> m;
	ans = 2e9;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
			if (arr[i][j] != 0 && arr[i][j] != 6)
				v.push_back(pos(i, j, arr[i][j]));
		}
	sort(v.begin(), v.end());
	dfs(0);
	cout << ans;
}