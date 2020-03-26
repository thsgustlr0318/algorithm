#include <iostream>
#include <algorithm>
using namespace std;
int ans, n, start_y, start_x;
int map[20][20], desert[101];
//desert[idx] = idx디저트를 파는 카페를 방문했는지 여부
int moveDir[4][2] = { {1, -1}, {1, 1}, {-1, 1}, {-1, -1} };
void dfs(int y, int x, int dir, int cnt)
{
    int ny = y + moveDir[dir][0], nx = x + moveDir[dir][1];
    //카페를 방문하여 처음으로 돌아왔을 때
    if (start_y == ny && start_x == nx && dir == 3) {
        ans = max(ans, cnt);
        return;
    }
    if (dir > 3 || ny < 0 || nx < 0 || ny >= n || nx >= n || desert[map[ny][nx]]) return;
    desert[map[ny][nx]] = true;
    //원래 방향으로 탐색
    dfs(ny, nx, dir, cnt + 1);
    //다음 방향으로 탐색
    dfs(ny, nx, dir + 1, cnt + 1);
    desert[map[ny][nx]] = false;
}
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        cin >> n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> map[i][j];
        for (int i = 0; i < n - 2; i++)
            for (int j = 1; j < n - 1; j++) {
                //처음 위치(start_x, start_y) 설정
                start_y = i, start_x = j;
                desert[map[i][j]] = true;
                dfs(i, j, 0, 1);
                desert[map[i][j]] = false;
            }
        if (ans == 0) ans = -1;
        cout << "#" << test_case << " " << ans << "\n";
        ans = 0;
    }
    return 0;
}