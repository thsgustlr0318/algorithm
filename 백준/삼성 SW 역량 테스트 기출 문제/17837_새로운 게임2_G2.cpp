#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct pos {
	int y, x, direction;
	pos(int a, int b, int c) {
		y = a, x = b, direction = c;
	}
};
int moveDir[4][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
int board[12][12];
vector<int> chess[12][12];	//각 체스판에 올라와있는 말들의 vector
vector<pos> horse;			//1번~k번 말의 상태
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	int n, k, ans;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> board[i][j];
	for (int i = 0; i < k; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		horse.push_back(pos(a - 1, b - 1, c - 1));
		chess[a - 1][b - 1].push_back(i);
	}
	for (ans = 1; ans <= 1000; ans++) {
		for (int idx = 0; idx < k; idx++) {
			int cur_y = horse[idx].y, cur_x = horse[idx].x, &dir = horse[idx].direction;
			int ny = cur_y + moveDir[dir][0], nx = cur_x + moveDir[dir][1];
			//파란칸
			if (ny < 0 || nx < 0 || ny >= n || nx >= n || board[ny][nx] == 2) {
				//방향 바꿈
				dir % 2 == 0 ? dir++ : dir--;
				ny = cur_y + moveDir[dir][0], nx = cur_x + moveDir[dir][1];
				//다음에도 파란칸이면 움직이지 않음
				if (ny < 0 || nx < 0 || ny >= n || nx >= n || board[ny][nx] == 2) continue;
			}
			vector<int>& cur = chess[cur_y][cur_x];
			auto it_idx = find(cur.begin(), cur.end(), idx);
			//빨간칸일경우 idx부터 reverse
			if (board[ny][nx] == 1) 
				reverse(it_idx, cur.end());			
			//다음칸으로 전부 움직임
			for (auto it = it_idx; it != cur.end(); it++) {
				horse[*it].y = ny, horse[*it].x = nx;
				chess[ny][nx].push_back(*it);
			}
			//움직인 말들 지움
			cur.erase(it_idx, cur.end());
			//칸에 말이 4개 이상일경우
			if (chess[ny][nx].size() >= 4) {
				cout << ans;
				return 0;
			}
		}		
	}
	cout << "-1";
}
//find, reverse등 iterator 사용 방법