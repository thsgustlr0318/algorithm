#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, d, ans;
int arr[16][16], visit[16][16];
int moveDir[3][2] = { {0, -1}, {-1, 0}, {0, 1} };
vector<int> archer;
vector<pair<int, int>> enemy;
void playGame()
{
	int temp[16][16], kill = 0;
	memcpy(temp, arr, sizeof(arr));	
	//turn = 적 이동 횟수
	for (int turn = 0; turn < n; turn++) {
		//3명의 궁수에 대해서 각각 가장 가까운 적 enemy vector에 넣음
		for (int i = 0; i < 3; i++) {	
			memset(visit, 0, sizeof(visit));
			queue<pair<int, int>> q;
			q.push({ n - turn, archer[i] });
			visit[n - turn][archer[i]] = 1;
			//bfs
			while (!q.empty()) {
				int y = q.front().first, x = q.front().second;
				q.pop();
				//범위 벗어나는 경우
				if (visit[y][x] > d + 1) continue;
				//범위안에 적이 있는 경우
				if (arr[y][x] == 1) {
					enemy.push_back({ y, x });
					break;
				}				
				for (int k = 0; k < 3; k++) {
					int ny = y + moveDir[k][0], nx = x + moveDir[k][1];
					if (ny < 0 || nx < 0 || ny >= n - turn || visit[ny][nx]) continue;
					visit[ny][nx] = visit[y][x] + 1;
					q.push({ ny, nx });					
				}
			}
		}
		//공격할 적 있는경우, 중복 제거
		if (!enemy.empty()) {
			sort(enemy.begin(), enemy.end());
			enemy.erase(unique(enemy.begin(), enemy.end()), enemy.end());
			for (int i = 0; i < enemy.size(); i++) {
				int ny = enemy[i].first, nx = enemy[i].second;
				arr[ny][nx] = 0;
				kill++;
			}
			enemy.clear();
		}
		//궁수 다음칸으로 설정
		for (int i = 0; i < m; i++)
			arr[n - turn - 1][i] = temp[n][i];
	}
	memcpy(arr, temp, sizeof(arr));
	ans = max(ans, kill);
}
//궁수 위치 설정
//3명 설정시 playGame
void dfs(int idx, int cnt)
{
	if (cnt == 3) {
		playGame();
		return;
	}
	for (int i = idx; i < m; i++) {
		arr[n][i] = 2;
		archer.push_back(i);
		dfs(i + 1, cnt+1);
		archer.pop_back();
		arr[n][i] = 0;
	}
}
int main()
{
	cin >> n >> m >> d;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) 
			cin >> arr[i][j];
	dfs(0, 0);
	cout << ans;
}
