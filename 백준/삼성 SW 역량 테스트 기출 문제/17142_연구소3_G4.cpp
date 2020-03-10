#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, ans = 2e9, one_count;
int arr[50][50], visit[50][50];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
deque<pair<int, int>> dq;
vector<pair<int, int>> virus;
void bfs(int cnt, int idx)
{
	if (cnt == m) {
		queue<pair<int, int>> q;
		memset(visit, 0, sizeof(visit));
		int blank_count = 0, maxv = 0;
		for (int i = 0; i < m; i++) {
			q.push(make_pair(dq[i].first, dq[i].second));
			visit[dq[i].first][dq[i].second] = 1;
		}
		while (!q.empty()) {
			int cur_y = q.front().first, cur_x = q.front().second;
			q.pop();
			for (int i = 0; i < 4; i++) {
				int ny = cur_y + moveDir[i][0], nx = cur_x + moveDir[i][1];
				if (ny < 0 || nx < 0 || ny >= n || nx >= n || visit[ny][nx] || arr[ny][nx] == 1) continue;
				q.push(make_pair(ny, nx));
				visit[ny][nx] = visit[cur_y][cur_x] + 1;
				blank_count++;
				if (arr[ny][nx] != 2) maxv = max(maxv, visit[ny][nx] - 1);
			}
		}
		if (one_count - m == blank_count)
			ans = min(ans, maxv);
		return;
	}
	int size = virus.size();
	for (int i = idx; i < size; i++) {
		arr[virus[i].first][virus[i].second] = 3;
		dq.push_back(virus[i]);
		bfs(cnt + 1, i + 1);
		dq.pop_back();
		arr[virus[i].first][virus[i].second] = 2;
	}
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	cin >> n >> m;
	one_count = n * n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) one_count--;
			if (arr[i][j] == 2) virus.push_back(make_pair(i, j));
		}
	bfs(0, 0);
	ans == 2e9 ? cout << "-1" : cout << ans;
}
//시간초과 해결
//활성화된 바이러스 조합 구하기 위해 virus vector 사용
//m크기만큼 deque에 활성화된 바이러스 넣어서 cnt == m인 경우 deque값을 queue에 복사 한 후 bfs
//다음 조합 확인하기 위해 deque에서 pop_back
//바이러스가 다 안퍼진 경우 확인하기 위해 one_count와 blank_count 사용