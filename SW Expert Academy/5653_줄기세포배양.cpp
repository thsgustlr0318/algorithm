#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <deque>
#define start 150
using namespace std;
struct cellInfo {
	int y, x, time;
};
int n, m, k, ans;
int board[350][350];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
deque<cellInfo> cells[11];
void init()
{
	memset(board, 0, sizeof(board));
	for (int i = 1; i <= 10; i++)
		cells[i].clear();
	ans = 0;
}
void spread(cellInfo cur, int life)
{
	int y = cur.y, x = cur.x;
	for (int i = 0; i < 4; i++) {
		int ny = y + moveDir[i][0], nx = x + moveDir[i][1];
		if (board[ny][nx]) continue;
		board[ny][nx] = life;
		cells[life].push_back({ ny, nx, 0 });
	}
}
void growCell()
{
	for (int life = 10; life >= 1; life--) {
		if (cells[life].empty()) continue;
		int cellsize = cells[life].size();
		for (int i = 0, idx = 0; i < cellsize; i++) {
			//세포 번식
			if (cells[life][idx].time == life)
				spread(cells[life][idx], life);
			//세포 시간 증가
			cells[life][idx].time++;
			//생명력*2만큼 살았을경우, 세포 죽음
			if (cells[life][idx].time == life * 2)
				cells[life].pop_front();
			else idx++;
		}
	}
}
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		init();
		cin >> n >> m >> k;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				cin >> board[start + i][start + j];
				if (board[start + i][start + j] != 0)
					cells[board[start + i][start + j]].push_back({ start + i, start + j, 0 });
			}
		for (int i = 1; i <= k; i++)
			growCell();
		for (int i = 1; i <= 10; i++)
			ans += cells[i].size();
		cout << "#" << test_case << " " << ans << "\n";
	}
	return 0;
}