#include<iostream>
#include <queue>
#include <string>
using namespace std;

struct pos {
	int ry, rx;
	int by, bx;
	int dep;
};
string board[10];
int visit[10][10][10][10];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> board[i];
	pos start;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 'R')
				start.ry = i, start.rx = j;
			if (board[i][j] == 'B')
				start.by = i, start.bx = j;
		}
	queue<pos> q;
	start.dep = 0;
	q.push(start);
	visit[start.ry][start.rx][start.by][start.bx] = true;
	while (!q.empty()) {
		pos cur = q.front();
		q.pop();
		bool blueflag;
		if (cur.dep > 10) {
			cout << "-1";
			return 0;
		}
		if (board[cur.ry][cur.rx] == 'O') {
			cout << cur.dep;
			return 0;
		}
		for (int i = 0; i < 4; i++) {
			pos next = cur;
			blueflag = false;
			while (1) {
				if (board[next.ry + moveDir[i][0]][next.rx + moveDir[i][1]] == 'O') {
					next.ry = next.ry + moveDir[i][0];
					next.rx = next.rx + moveDir[i][1];
					break;
				}
				else if (board[next.ry + moveDir[i][0]][next.rx + moveDir[i][1]] == '#')
					break;
				else {
					next.ry = next.ry + moveDir[i][0];
					next.rx = next.rx + moveDir[i][1];
				}
			}
			while (1) {
				if (board[next.by + moveDir[i][0]][next.bx + moveDir[i][1]] == 'O') {
					blueflag = true;
					break;
				}
				else if (board[next.by + moveDir[i][0]][next.bx + moveDir[i][1]] == '#')
					break;
				else {
					next.by = next.by + moveDir[i][0];
					next.bx = next.bx + moveDir[i][1];
				}
			}
			if (blueflag)
				continue;

			if (next.rx == next.bx && next.ry == next.by) {
				if (i == 0)
					cur.ry > cur.by ? next.by-- : next.ry--;
				else if (i == 1)
					cur.ry > cur.by ? next.ry++ : next.by++;
				else if (i == 2)
					cur.rx > cur.bx ? next.bx-- : next.rx--;
				else
					cur.rx > cur.bx ? next.rx++ : next.bx++;
			}
			if (!visit[next.ry][next.rx][next.by][next.bx]) {
				next.dep = cur.dep + 1;
				q.push(next);
				visit[next.ry][next.rx][next.by][next.bx] = true;
			}
		}
	}
	cout << "-1";
	return 0;
}