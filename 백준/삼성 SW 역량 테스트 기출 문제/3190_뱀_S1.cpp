#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

#define blank 0
#define wall 1
#define apple 2
#define snake 3
struct  active{
	int time;
	char dir;
	active(int a, char b) {
		time = a, dir = b;
	}
};
int n, k, l, arr[102][102], ans;
int moveDir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
void make_board() {
	int i, j;
	for (i = 0, j = 0; j <= n + 1; j++) arr[i][j] = wall;
	for (i = 0, j = 0; i <= n + 1; i++) arr[i][j] = wall;
	for (i = n + 1, j = 0; j <= n + 1; j++) arr[i][j] = wall;
	for (j = n + 1, i = 0; i <= n + 1; i++) arr[i][j] = wall;
}
int main()
{	
	queue<active> q;
	deque<pair<int, int>> sq;
	int hy = 1, hx = 1, ty = 1, tx = 1, dir = 0;

	cin >> n >> k;
	make_board();
	for (int i = 0; i < k; i++) {
		int y, x;
		cin >> y >> x;
		arr[y][x] = apple;
	}
	cin >> l;
	
	for (int i = 0; i < l; i++) {
		int t;
		char d;
		cin >> t >> d;
		q.push(active(t, d));
	}
		
	active cur = q.front();
	q.pop();	
	sq.push_back(make_pair(1, 1));
	arr[1][1] = snake;

	while (1) {
		ans++;
		hy += moveDir[dir][0], hx += moveDir[dir][1];
		sq.push_back(make_pair(hy, hx));

		if (arr[hy][hx] == wall || arr[hy][hx] == snake)
			break;
		else if (arr[hy][hx] == blank) {
			ty = sq.front().first, tx = sq.front().second;
			sq.pop_front();
			arr[ty][tx] = blank;
			arr[hy][hx] = snake;
		}
		else if (arr[hy][hx] == apple) {
			arr[hy][hx] = snake;
		}

		if (ans == cur.time) {
			if (cur.dir == 'D')
				dir = (dir + 1) % 4;
			else
				dir = (dir - 1 + 4) % 4;
			if (!q.empty()) {
				cur = q.front();
				q.pop();
			}
		}
	}
	cout << ans;
}