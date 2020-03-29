#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int ans, n, m, r, c, l;
int map[50][50], visit[50][50];
//상 하 좌 우
int moveDir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
//2, 3, 4, 5, 6, 7번 블록의 가능한 방향
int tunnel[8][2] = { {}, {}, {0, 1}, {2, 3}, {0, 3}, {1, 3}, {1, 2}, {0, 2} };
bool check(int dir, int ny, int nx)
{
    if (dir == 0 && (map[ny][nx] == 3 || map[ny][nx] == 4 || map[ny][nx] == 7)) return false;
    else if (dir == 1 && (map[ny][nx] == 3 || map[ny][nx] == 5 || map[ny][nx] == 6)) return false;
    else if (dir == 2 && (map[ny][nx] == 2 || map[ny][nx] == 6 || map[ny][nx] == 7)) return false;
    else if (dir == 3 && (map[ny][nx] == 2 || map[ny][nx] == 4 || map[ny][nx] == 5)) return false;
    return true;
}
void bfs()
{
    queue<pair<int, int>> q;
    visit[r][c] = 1;
    q.push({ r, c });
    while (!q.empty()) {
        int y = q.front().first, x = q.front().second;
        q.pop();
        //소요된 시간이 l이상이면 탐색 금지
        if (visit[y][x] == l) continue;
        //1번블록 (상, 하, 좌, 우)
        if (map[y][x] == 1) {
            for (int i = 0; i < 4; i++) {
                int ny = y + moveDir[i][0], nx = x + moveDir[i][1];
                if (ny < 0 || nx < 0 || ny >= n || nx >= m || visit[ny][nx] || !map[ny][nx]) continue;
                if (!check(i, ny, nx)) continue;
                visit[ny][nx] = visit[y][x] + 1;
                q.push({ ny, nx });
                ans++;
            }
        }
        //2~7번 블록
        else {
            for (int i = 0; i < 2; i++) {
                int ny = y + moveDir[tunnel[map[y][x]][i]][0], nx = x + moveDir[tunnel[map[y][x]][i]][1];
                if (ny < 0 || nx < 0 || ny >= n || nx >= m || visit[ny][nx] || !map[ny][nx]) continue;
                if (!check(tunnel[map[y][x]][i], ny, nx)) continue;
                visit[ny][nx] = visit[y][x] + 1;
                q.push({ ny, nx });
                ans++;
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
        cin >> n >> m >> r >> c >> l;
        ans = 1;
        for(int i=0; i<n; i++)
            for (int j = 0; j < m; j++) 
                cin >> map[i][j];
        bfs();
        cout << "#" << test_case << " " << ans << "\n";        
        memset(visit, 0, sizeof(visit));
    }
    return 0;
}