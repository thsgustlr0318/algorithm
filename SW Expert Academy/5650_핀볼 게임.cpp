#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct ballPos {
	int y, x, dir;
	ballPos(int a, int b, int c) {
		y = a, x = b, dir = c;
	}
};
int n, ans = 0;
int board[100][100];
int moveDir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
vector<pair<int, int>> blank;
vector<pair<int, int>> wormholl[5];
void changeDirTriangle(int& dir, int wallCase)
{
	if (wallCase == 1) dir == 2 ? dir = 1 : dir = 0;
	else if (wallCase == 2) dir == 0 ? dir = 1 : dir = 2;
	else if (wallCase == 3) dir == 0 ? dir = 3 : dir = 2;
	else dir == 1 ? dir = 0 : dir = 3;
}
void changeDirWall(int &dir)
{
	if (dir == 0) dir = 2;
	else if (dir == 1) dir = 3;
	else if (dir == 2) dir = 0;
	else dir = 1;
}
void passWormHoll(int& y, int& x, int hollnum)
{
	if (wormholl[hollnum][0].first == y && wormholl[hollnum][0].second == x)
		y = wormholl[hollnum][1].first, x = wormholl[hollnum][1].second;
	else
		y = wormholl[hollnum][0].first, x = wormholl[hollnum][0].second;
}
void playGame(ballPos ball)
{
	int y = ball.y, x = ball.x, dir = ball.dir;
	int ny = y, nx = x;
	int cnt = 0;
	while (1) {
		ny = y + moveDir[dir][0], nx = x + moveDir[dir][1];
		//벽 or 5번
		if (ny < 0 || nx < 0 || ny >= n || nx >= n || board[ny][nx] == 5) {
			cnt++;
			y = ny, x = nx;
			changeDirWall(dir);
			continue;
		}
		//빈공간
		else if (board[ny][nx] == 0 && !(ny==ball.y && nx==ball.x)) {
			y = ny, x = nx;
			continue;
		}
		//1, 2, 3, 4번
		else if (board[ny][nx] == 1 || board[ny][nx] == 2 || board[ny][nx] == 3 || board[ny][nx] == 4) {			
			if (dir == board[ny][nx] - 1 || dir == (board[ny][nx] % 4)) {
				y = ny, x = nx;
				changeDirWall(dir);
			}
			else {
				y = ny, x = nx;
				changeDirTriangle(dir, board[ny][nx]);
			}
			cnt++;
			continue;
		}
		//블랙홀
		else if (board[ny][nx] == -1 || (ny == ball.y && nx == ball.x))
			break;
		//웜홀
		else {
			passWormHoll(ny, nx, board[ny][nx] - 6);
			y = ny, x = nx;
		}
	}
	ans = max(ans, cnt);
}
void initGame()
{
	for (int i = 0; i < 5; i++)
		wormholl[i].clear();
	blank.clear();
	ans = 0;
}
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{		
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> board[i][j];
				if (board[i][j] == 0)
					blank.push_back({ i, j });
				else if (6 <= board[i][j] && board[i][j] <= 10) 
					wormholl[board[i][j] - 6].push_back({ i, j });				
			}
		int bsize = blank.size();
		for (int i = 0; i < bsize; i++)
			for (int dir = 0; dir < 4; dir++)
				playGame(ballPos(blank[i].first, blank[i].second, dir));
		cout << "#" << test_case << " " << ans << "\n";
		initGame();
	}
	return 0;
}