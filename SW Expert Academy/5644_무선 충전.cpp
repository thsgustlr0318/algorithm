#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
//BC의 성능과 BC의 번호
struct bcInfo {
	int p, idx;
};
//map[y][x] = (y, x)좌표의 BC의 성능과 번호
vector<bcInfo> map[10][10];
//0: 가만히, 1: 위, 2: 오른쪽, 3: 아래, 4: 왼쪽
int moveDir[5][2] = { {0, 0}, {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
//auser[idx], buser[idx] = idx시간의 A와 B의 이동 정보
int auser[101], buser[101];
int m, a, ans;
//A와 B의 현재 위치
pair<int, int> apos, bpos;
void init()
{
	apos = { 0 ,0 }, bpos = { 9, 9 };
	auser[0] = buser[0] = 0;
	ans = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			map[i][j].clear();
}
void setMap(int x, int y, int c, int p, int idx)
{
	//BFS로 C칸 안에 있는 map[i][j]에 정보 push_back
	int visit[10][10] = { 0 };
	queue<pair<int, int>> q;
	q.push({ y, x });
	visit[y][x] = 1;
	map[y][x].push_back({ p, idx });
	while (!q.empty()) {
		int cy = q.front().first, cx = q.front().second;
		q.pop();
		if (visit[cy][cx] >= c + 1) continue;
		for (int i = 1; i <= 4; i++) {
			int ny = cy + moveDir[i][0], nx = cx + moveDir[i][1];
			if (ny < 0 || nx < 0 || ny >= 10 || nx >= 10 || visit[ny][nx]) continue;
			visit[ny][nx] = visit[cy][cx] + 1;
			q.push({ ny, nx });
			map[ny][nx].push_back({ p, idx });
		}
	}
}
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)	{
		cin >> m >> a;
		init();
		for (int i = 1; i <= m; i++)	cin >> auser[i];
		for (int i = 1; i <= m; i++)	cin >> buser[i];
		for (int i = 0; i < a; i++) {
			int x, y, c, p;
			cin >> x >> y >> c >> p;
			setMap(x - 1, y - 1, c, p, i);
		}
		for (int time = 0; time <= m; time++) {
			int& ay = apos.first, & ax = apos.second, & by = bpos.first, & bx = bpos.second;
			ay += moveDir[auser[time]][0], ax += moveDir[auser[time]][1];
			by += moveDir[buser[time]][0], bx += moveDir[buser[time]][1];
			int maxp = 0;
			//B만 배터리 충전
			if (map[ay][ax].size() == 0 && map[by][bx].size() != 0) {				
				for (int i = 0; i < map[by][bx].size(); i++) 
					maxp = max(maxp, map[by][bx][i].p);		
			}
			//A만 배터리 충전
			else if (map[ay][ax].size() != 0 && map[by][bx].size() == 0) {
				for (int i = 0; i < map[ay][ax].size(); i++) 
					maxp = max(maxp, map[ay][ax][i].p);		
			}
			//A, B 모두 배터리 충전
			else if (map[ay][ax].size() >= 1 && map[by][bx].size() >= 1) {
				//모든 경우의 수 확인
				for(int i=0; i<map[ay][ax].size(); i++)
					for (int j = 0; j < map[by][bx].size(); j++) {
						int a_bc = map[ay][ax][i].idx, b_bc = map[by][bx][j].idx, ap = map[ay][ax][i].p, bp = map[by][bx][j].p;
						if (a_bc == b_bc) maxp = max(maxp, ap);
						else 	maxp = max(maxp, ap + bp);
					}				
			}
			ans += maxp;
		}
		cout << "#" << test_case << " " << ans << "\n";
	}	
	return 0;
}