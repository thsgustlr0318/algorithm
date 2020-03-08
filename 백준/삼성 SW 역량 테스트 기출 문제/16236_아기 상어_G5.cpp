#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int board[20][20], visit[20][20];
int moveDir[4][2] = { {-1, 0} , {0, -1}, {0, 1}, {1, 0} };
int n, shark_y, shark_x, shark_size = 2, eat, ans;
struct pos {
	int y, x, depth;
	pos(int a, int b, int c) {
		y = a, x = b, depth = c;
	}
	bool operator <(const pos &a) const {
		if (depth == a.depth) {
			if (y == a.y)
				return x < a.x;
			return y < a.y;
		}
		return depth < a.depth;
	}
};
int main()
{
	cin >> n;
	for(int i=0; i<n; i++)
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
			if (board[i][j] == 9)
				shark_y = i, shark_x = j;
		}
	while (1) {
		queue<pair<int, int>> q;
		vector<pos> v;
		q.push(make_pair(shark_y, shark_x));
		visit[shark_y][shark_x] = 1;
		while (!q.empty()) {
			int cur_y = q.front().first, cur_x = q.front().second;
			q.pop();
			if (board[cur_y][cur_x] != 0  && board[cur_y][cur_x] < shark_size) 
				v.push_back(pos(cur_y, cur_x, visit[cur_y][cur_x] - 1));
			
			for (int i = 0; i < 4; i++) {
				int ny = cur_y + moveDir[i][0], nx = cur_x + moveDir[i][1];
				if (ny < 0 || nx<0 || ny >= n || nx >= n || visit[ny][nx] || board[ny][nx] > shark_size) continue;
				q.push(make_pair(ny, nx));
				visit[ny][nx] = visit[cur_y][cur_x] + 1;
			}
		}
		if (v.size() == 0) break;
		sort(v.begin(), v.end());
		eat++,	ans += v[0].depth;
		board[v[0].y][v[0].x] = 0;
		board[shark_y][shark_x] = 0;
		shark_y = v[0].y, shark_x = v[0].x;
		if (eat == shark_size) 
			shark_size++, eat = 0;		
		memset(visit, 0, sizeof(visit));		
	}
	cout << ans;
}
//bfs
//물고기 조건 맞추기 위해 가능한 물고기 vector에 넣어서 길이, y, x축 순으로 정렬