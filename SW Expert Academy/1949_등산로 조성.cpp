#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int ans, n, k;
int map[8][8];
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
//최대 등산로 길이 찾기
void dfs(int y, int x, int depth)
{
    for (int i = 0; i < 4; i++) {
        int ny = y + moveDir[i][0], nx = x + moveDir[i][1];
        if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
        if (map[ny][nx] < map[y][x])
            dfs(ny, nx, depth + 1);
    }
    ans = max(ans, depth);
}
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        cin >> n >> k;
        //top = 가장 높은 봉우리 크기
        int top = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> map[i][j];
                top = max(top, map[i][j]);
            }
        //pos = 가장 높은 봉우리들의 y, x좌표
        vector<pair<int, int>> pos;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (map[i][j] == top)
                    pos.push_back({ i, j });
            }
        //지형을 깎지 않았을 때
        for (int idx = 0; idx < pos.size(); idx++)
            dfs(pos[idx].first, pos[idx].second, 1);
        //모든 map[i][j]에 대해서 최대 k만큼 깎았을 때
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int temp = map[i][j];
                //map[i][j]에 해당하는 봉우리 깎기
                for (int l = 1; l <= k; l++) {
                    map[i][j]--;
                    //가장 높은 봉우리들에서 탐색
                    for (int idx = 0; idx < pos.size(); idx++) 
                        dfs(pos[idx].first, pos[idx].second, 1);
                }
                map[i][j] = temp;
            }
        }
        cout << "#" << test_case << " " << ans << "\n";
        ans = 0;
    }
    return 0;
}