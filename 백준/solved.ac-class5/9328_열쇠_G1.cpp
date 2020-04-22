#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int h, w, ans = 0;
		cin >> h >> w;
		vector<string> map(h);
		vector<bool> key(26, false);
		queue<pair<int, int>> door[26], q;
		bool visit[100][100] = { false };
		string key_str;
		//지도, 열쇠 입력
		for (int i = 0; i < h; i++)
			cin >> map[i];
		cin >> key_str;
		//열쇠 설정
		if (key_str.compare("0") != 0) {
			for (int i = 0; i < key_str.size(); i++)
				key[key_str[i] - 'a'] = true;
		}
		//가장자리 탐색해서 들어갈 수 있는곳 찾음
		//빈벽: q, 문: door, 열쇠: q, 설정
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (i == 0 || j == 0 || i == h - 1 || j == w - 1) {
					if (map[i][j] == '.' || map[i][j] == '$') {
						q.push({ i, j });
						visit[i][j] = true;
					}
					else if ('A' <= map[i][j] && map[i][j] <= 'Z') {
						door[map[i][j] - 'A'].push({ i, j });
					}
					else if ('a' <= map[i][j] && map[i][j] <= 'z') {
						q.push({ i, j });
						visit[i][j] = true;
						key[map[i][j] - 'a'] = true;
					}
				}
		//열쇠 있으면, 해당하는 열쇠로 열 수 있는 문들 q에 넣음
		for (int i = 0; i < 26; i++)
			if (key[i]) {
				while (!door[i].empty()) {
					q.push(door[i].front());
					map[door[i].front().first][door[i].front().second] = '.';
					visit[door[i].front().first][door[i].front().second] = true;
					door[i].pop();
				}
			}
		//BFS
		while (!q.empty()) {
			int y = q.front().first, x = q.front().second;
			q.pop();
			if (map[y][x] == '$')
				ans++;
			for (int i = 0; i < 4; i++) {
				int ny = y + moveDir[i][0], nx = x + moveDir[i][1];
				if (ny < 0 || nx < 0 || ny >= h || nx >= w || visit[ny][nx] || map[ny][nx] == '*') continue;
				char& c = map[ny][nx];
				visit[ny][nx] = true;
				if ('A' <= c && c <= 'Z') {
					if (key[c - 'A'])
						q.push({ ny, nx });
					else
						door[c - 'A'].push({ ny, nx });
				}
				else if ('a' <= c && c <= 'z') {
					key[c - 'a'] = true;
					q.push({ ny, nx });
					while (!door[c - 'a'].empty()) {
						q.push(door[c - 'a'].front());
						visit[door[c - 'a'].front().first][door[c - 'a'].front().second] = true;
						door[c - 'a'].pop();
					}
				}
				else {
					q.push({ ny, nx });
				}
			}
		}
		cout << ans << "\n";
	}
}