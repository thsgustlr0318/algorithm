#include <iostream>
#include <queue>
#include <vector>
#include <math.h>
#include <cstring>
using namespace std;
int arr[50][50], n, l, r, ans;
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
bool visit[50][50];
int main()
{
	cin >> n >> l >> r;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];
	while (1) {
		int count = 0;
		for (int y = 0; y < n; y++)
			for (int x = 0; x < n; x++) {
				if (visit[y][x])	 continue;
				queue<pair<int, int>> q;
				vector<pair<int, int>> v;
				int sum = arr[y][x];
				q.push(make_pair(y, x));
				v.push_back(make_pair(y, x));
				visit[y][x] = true;
				count++;
				while (!q.empty()) {
					int cur_y = q.front().first, cur_x = q.front().second;
					q.pop();
					for (int i = 0; i < 4; i++) {
						int next_y = cur_y + moveDir[i][0], next_x = cur_x + moveDir[i][1];
						if (next_y < 0 || next_x < 0 || next_y >= n || next_x >= n || visit[next_y][next_x]) continue;
						if (abs(arr[cur_y][cur_x] - arr[next_y][next_x]) < l || abs(arr[cur_y][cur_x] - arr[next_y][next_x]) > r) continue;
						visit[next_y][next_x] = true;
						q.push(make_pair(next_y, next_x));
						v.push_back(make_pair(next_y, next_x));
						sum += arr[next_y][next_x];
					}
				}
				int avg = sum / v.size();
				for (int i = 0; i < v.size(); i++)
					arr[v[i].first][v[i].second] = avg;
			}
		if (count == n * n) break;
		ans++;
		memset(visit, false, sizeof(visit));
	}
	cout << ans;
}
//bfs