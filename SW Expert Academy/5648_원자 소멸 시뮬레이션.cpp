#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
struct atomInfo {
	int x, y, dir, energy, live, turn;
};
atomInfo visit[1001];
int map[2001][2001];
int moveDir[4][2] = { {1, 0},{-1, 0},{0, -1},{0, 1} };
int ans;
void moveAtom(atomInfo& a)
{
	a.y += moveDir[a.dir][0];
	a.x += moveDir[a.dir][1];
	a.turn++;
}
void init()
{
	ans = 0;
	memset(map, 0, sizeof(map));
}
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int test_case;
	int T;

	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			visit[i] = { a + 1000, b + 1000, c, d , 1, 0 };
			map[b + 1000][a + 1000] = i;
		}
		for (int time = 0, cnt = n; time < 2000 && cnt > 0; time++) {
			for (int idx = 1; idx <= n; idx++) {
				if (visit[idx].live) {
					if (idx == map[visit[idx].y][visit[idx].x])
						map[visit[idx].y][visit[idx].x] = 0;
					moveAtom(visit[idx]);
					//cur = 이동된 idx 원자 정보
					atomInfo& cur = visit[idx];
					//범위 벗어나는 경우, 해당 원자 죽이고 continue
					if (cur.y < 0 || cur.x < 0 || cur.y>2000 || cur.x>2000) {
						cur.live = 0;
						cnt--;
						continue;
					}
					//next = 이동될 칸에 이미 존재하는 원자 정보
					atomInfo& next = visit[map[visit[idx].y][visit[idx].x]];
					//중간에서 충돌
					if (map[visit[idx].y][visit[idx].x] != 0 && cur.turn - 1 == next.turn && next.live == 1 && (cur.dir + next.dir == 1 || cur.dir + next.dir == 5)) {
						cur.live = 0, next.live = 0;
						ans += cur.energy + next.energy;
						cnt -= 2;
					}
					//원자 같은 점에서 충돌
					else if (map[visit[idx].y][visit[idx].x] != 0 && cur.turn == next.turn) {
						if (next.live == 1) ans += next.energy, next.live = 0, cnt--;
						cur.live = 0;
						ans += cur.energy;
						cnt--;
					}
					else {
						map[visit[idx].y][visit[idx].x] = idx;
					}
				}
			}
		}
		cout << "#" << test_case << " " << ans << "\n";
		init();
	}
	return 0;
}