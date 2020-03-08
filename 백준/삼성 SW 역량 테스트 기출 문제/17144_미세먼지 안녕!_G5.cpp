#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int room[50][50];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int main()
{
	int r, c, t, clean_up = -1, clean_down, ans = 0;
	cin >> r >> c >> t;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			cin >> room[i][j];
			if (room[i][j] == -1)
				clean_up == -1 ? clean_up = i : clean_down = i;
		}
	vector<pair<int, int>> up, down;
	//위쪽 순환 순서
	for (int i = 1; i < c; i++)
		up.push_back(make_pair(clean_up, i));
	for (int i = clean_up - 1; i >= 0; i--)
		up.push_back(make_pair(i, c - 1));
	for (int i = c - 2; i >= 0; i--)
		up.push_back(make_pair(0, i));
	for (int i = 1; i < clean_up; i++)
		up.push_back(make_pair(i, 0));
	//아래쪽 순환 순서
	for (int i = 1; i < c; i++)
		down.push_back(make_pair(clean_down, i));
	for (int i = clean_down + 1; i < r; i++)
		down.push_back(make_pair(i, c - 1));
	for (int i = c - 2; i >= 0; i--)
		down.push_back(make_pair(r - 1, i));
	for (int i = r - 2; i > clean_down; i--)
		down.push_back(make_pair(i, 0));
	while (t--) {
		//확산
		int temp[50][50];
		memcpy(temp, room, sizeof(room));
		for (int y = 0; y < r; y++)
			for (int x = 0; x < c; x++) {
				if (temp[y][x] == 0 || temp[y][x] == -1 || temp[y][x] < 5) continue;
				int cnt = 0;
				for (int i = 0; i < 4; i++) {
					int ny = y + moveDir[i][0], nx = x + moveDir[i][1];
					if (ny < 0 || nx < 0 || ny >= r || nx >= c || temp[ny][nx] == -1) continue;
					cnt++;
					room[ny][nx] += temp[y][x] / 5;
				}
				room[y][x] -= temp[y][x] / 5 * cnt;
			}
		//공기청정기
		memcpy(temp, room, sizeof(room));
		//위쪽
		for (int i = 1, size = up.size(); i < size; i++)
			room[up[i].first][up[i].second] = temp[up[i - 1].first][up[i - 1].second];
		room[up[0].first][up[0].second] = 0;
		//아래쪽
		for (int i = 1, size = down.size(); i < size; i++)
			room[down[i].first][down[i].second] = temp[down[i - 1].first][down[i - 1].second];
		room[down[0].first][down[0].second] = 0;
	}
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (room[i][j] != -1 && room[i][j] != 0)
				ans += room[i][j];
		}
	cout << ans;
}