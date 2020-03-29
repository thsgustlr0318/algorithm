#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Info {
    int y, x, num, dir;
};
//mapInfo map[i][j].maxnum = 최대 미생물 사이즈 크기, total = 합쳐진 미생물 크기
struct mapInfo {
    int maxnum, total;
};
int ans, n, m, k;
int moveDir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
//group[idx] = idx번 미생물의 정보, 죽은경우 Info.num = 0
Info group[1000];
mapInfo map[100][100];
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        cin >> n >> m >> k;
        for (int i = 0; i < k; i++) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            group[i] = { a, b, c, d - 1 };
        }
        for (int time = 0; time < m; time++) {
            //미생물 움직이기
            for (int idx = 0; idx < k; idx++) {
                Info& cur = group[idx];
                //죽은경우, continue
                if (cur.num == 0)  continue;
                cur.y += moveDir[cur.dir][0], cur.x += moveDir[cur.dir][1];
                //가장자리 만난경우
                if (cur.y == 0 || cur.x == 0 || cur.y == n - 1 || cur.x == n - 1) {
                    if (cur.dir == 0) cur.dir = 1;
                    else if (cur.dir == 1) cur.dir = 0;
                    else if (cur.dir == 2) cur.dir = 3;
                    else if (cur.dir == 3) cur.dir = 2;
                    cur.num /= 2;
                }
                //map의 최대 미생물 크기 설정
                if (map[cur.y][cur.x].maxnum < cur.num) 
                    map[cur.y][cur.x].maxnum = cur.num;                
                //map의 합쳐진 미생물 크기
                map[cur.y][cur.x].total += cur.num;
            }
            for (int idx = 0; idx < k; idx++) {
                Info& cur = group[idx];
                //죽은 경우, continue
                if (cur.num == 0) continue;
                //여러 미생물이 만났을 때, maxnum보다 작으면 죽임
                if (map[cur.y][cur.x].maxnum > cur.num) cur.num = 0;
                //가장 큰 미생물의 경우, 합쳐진 미생물 크기로 설정
                else cur.num = map[cur.y][cur.x].total;
            }
            //map 초기화
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    map[i][j].maxnum = 0, map[i][j].total = 0;
        }
        for (int i = 0; i < k; i++) {
            if (group[i].num != 0)
                ans += group[i].num;
        }
        cout << "#" << test_case << " " << ans << "\n";
        ans = 0;
    }
    return 0;
}