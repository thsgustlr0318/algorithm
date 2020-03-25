#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int map[20][20], visit[20][20];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int cost[22];
//cost[1]+...+cost[idx] = 1 ~ idx 범위 안(서비스 영역)에 있는 집의 갯수
int ans, n, m;
void bfs(int i, int j, int k)
{
    queue<pair<int, int>> q;
    visit[i][j] = 1;
    q.push({ i, j });
    while (!q.empty()) {
        int y = q.front().first, x = q.front().second;
        q.pop();
        if (map[y][x]) cost[visit[y][x]]++;
        if (visit[y][x] == k) continue;
        for (int l = 0; l < 4; l++) {
            int ny = y + moveDir[l][0], nx = x + moveDir[l][1];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n || visit[ny][nx]) continue;
            visit[ny][nx] = visit[y][x] + 1;
            q.push({ ny, nx });
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
        cin >> n >> m;
        int house_cnt = 0, max_k = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> map[i][j];
                if (map[i][j] == 1) house_cnt++;
            }
        //최대 서비스 영역 크기(MAX = n + 1)
        while (house_cnt * m >= max_k * max_k + (max_k - 1) * (max_k - 1) && max_k <= n) max_k++;
        //모든 map에서 max_k만큼 탐색
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                memset(cost, 0, sizeof(cost));
                memset(visit, 0, sizeof(visit));
                bfs(i, j, max_k);
                //탐색 후 서비스 제공 조건에 맞으면 ans 갱신
                int sum = 0;
                for (int k = 1; k <= max_k; k++) {
                    sum += cost[k];
                    if (sum * m - (k * k + (k - 1) * (k - 1)) >= 0)
                        ans = max(ans, sum);
                }
            }
        cout << "#" << test_case << " " << ans << "\n";
        ans = 0;
    }
    return 0;
}