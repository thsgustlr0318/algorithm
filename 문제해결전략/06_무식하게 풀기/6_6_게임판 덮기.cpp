#include <iostream>
#include <vector>
#include <string>
using namespace std;
//주어진 칸을 덮을 수 있는 4가지 방법
const int coverType[4][3][2] = {
	{{0, 0}, {1, 0}, {0, 1}},
	{{0, 0}, {0, 1}, {1, 1}},
	{{0, 0}, {1, 0}, {1, 1}},
	{{0, 0}, {1, 0}, {1, -1}}
};
//board의 (y, x)를 type번 방법으로 덮거나, 덮었던 블록을 없앤다
//delta = 1이면 덮고, -1이면 덮었던 블록을 없앤다
//만약 블록이 제대로 덮이지 않은 경우(게임판 밖, 겹치거나, 검은 칸 덮을때) false 반환
bool set(vector<vector<int>>& board, int y, int x, int type, int delta)
{
	bool ok = true;
	for (int i = 0; i < 3; i++) {
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
			ok = false;
		else if ((board[ny][nx] += delta) > 1)
			ok = false;
	}
	return ok;
}
//board의 모든 빈 칸을 덮을 수 있는 방법의 수 반환
//board[i][j] = 1 이미 덮인 칸 or 검은 칸
//board[i][j] = 0 아직 덮이지 않은 칸
int cover(vector<vector<int>>& board)
{
	int y = -1, x = -1;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++)
			if (board[i][j] == 0) {
				y = i, x = j;
				break;
			}
		if (y != -1) break;
	}
	//기저사례: 모든 칸을 채웠으면 1 반환
	if (y == -1) return 1;
	int ret = 0;
	for (int type = 0; type < 4; type++) {
		if (set(board, y, x, type, 1))
			ret += cover(board);
		set(board, y, x, type, -1);
	}
	return ret;
}
int main()
{
	int c, h, w;
	char ch;
	cin >> c;
	while (c--) {		
		cin >> h >> w;
		vector<vector<int>> board(h, vector<int>(w));
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				cin >> ch;
				ch == '#' ? board[i][j] = 1 : board[i][j] = 0;
		}
		cout << cover(board) << "\n";
	}
}