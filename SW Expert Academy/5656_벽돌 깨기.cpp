#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
int board[15][12];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int n, w, h, ans, score, total;
void initGame()
{
	memset(board, 0, sizeof(board));
	total = score = 0;
	ans = 2e9;
}
//벽돌 제거된 후 내리기
void setBlock()
{
	for (int i = 0; i < w; i++) {
		stack<int> s;
		for (int j = 0; j < h; j++) {
			if (board[j][i] != 0) {
				s.push(board[j][i]);
				board[j][i] = 0;
			}
		}
		int idx = h - 1;
		while (!s.empty()) {
			board[idx--][i] = s.top();
			s.pop();
		}
	}
}
//(y, x)좌표의 벽돌 range만큼 제거
void removeBlock(int y, int x, int range)
{
	if (board[y][x] != 0) {
		board[y][x] = 0;
		score--;
	}
	for (int i = 0; i < 4; i++) {
		int ny = y, nx = x;
		for (int j = 0; j < range - 1; j++) {
			ny += moveDir[i][0], nx += moveDir[i][1];
			if (ny < 0 || nx < 0 || ny >= h || nx >= w || board[ny][nx] == 0) continue;
			int prev = board[ny][nx];
			board[ny][nx] = 0;
			score--;
			if (prev > 1) removeBlock(ny, nx, prev);
		}
	}
}
//최대 n만큼 구슬 선택
void selectBall(int cnt)
{
	if (cnt == n) 
		return;	
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (board[j][i] != 0) {
				int temp[15][12], prev = score;
				memcpy(temp, board, sizeof(board));
				removeBlock(j, i, board[j][i]);
				setBlock();
				ans = min(ans, score);
				selectBall(cnt + 1);
				memcpy(board, temp, sizeof(board));
				score = prev;
				break;
			}
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
		cin >> n >> w >> h;
		initGame();
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				cin >> board[i][j];
				if (board[i][j] != 0) total++;
			}
		score = total;
		selectBall(0);
		cout << "#" << test_case << " " << ans << "\n";
	}
	return 0;
}