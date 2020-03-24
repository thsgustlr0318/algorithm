#include <iostream>
#include <cstring>
using namespace std;
int ans, n, x;
int map[20][20];
bool used[20][20];
//used: 경사로를 설치 했는지 유무
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int test_case;
    int T, num, dir;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        cin >> n >> x;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> map[i][j];
        //used 초기화
        memset(used, false, sizeof(used));
        //가로
        for (int ny = 0; ny < n; ny++) {
            bool flag = true;
            for (int nx = 0; nx < n - 1 && flag; nx++) {
                //2칸 이상 차이
                if (abs(map[ny][nx] - map[ny][nx + 1]) >= 2) flag = false;
                //한칸 높아질 때
                else if (map[ny][nx] - map[ny][nx + 1] == -1) {
                    if (nx - x + 1 < 0) {
                        flag = false;
                        continue;
                    }
                    for (int cnt = 1; cnt < x; cnt++) {
                        if (map[ny][nx] != map[ny][nx - cnt] || used[ny][nx - cnt]) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) continue;
                    for (int cnt = 0; cnt < x; cnt++)
                        used[ny][nx - cnt] = true;
                }
                //한칸 낮아질 때
                else if (map[ny][nx] - map[ny][nx + 1] == 1) {
                    if (nx + x >= n) {
                        flag = false;
                        break;
                    }
                    for (int cnt = 2; cnt <= x; cnt++) {
                        if (map[ny][nx + 1] != map[ny][nx + cnt] || used[ny][nx + cnt]) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) break;
                    for (int cnt = 1; cnt <= x; cnt++)
                        used[ny][nx + cnt] = true;
                    nx += x - 1;
                }
            }
            if (flag)
                ans++;
        }
        //used 초기화
        memset(used, false, sizeof(used));
        //세로
        for (int nx = 0; nx < n; nx++) {
            bool flag = true;
            for (int ny = 0; ny < n - 1 && flag; ny++) {
                //2칸 이상 차이
                if (abs(map[ny][nx] - map[ny + 1][nx]) >= 2) flag = false;
                //한칸 높아질 때
                else if (map[ny][nx] - map[ny + 1][nx] == -1) {
                    if (ny - x + 1 < 0) {
                        flag = false;
                        continue;
                    }
                    for (int cnt = 1; cnt < x; cnt++) {
                        if (map[ny][nx] != map[ny - cnt][nx] || used[ny - cnt][nx]) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) continue;
                    for (int cnt = 0; cnt < x; cnt++)
                        used[ny - cnt][nx] = true;
                }
                //한칸 낮아질 때
                else if (map[ny][nx] - map[ny + 1][nx] == 1) {
                    if (ny + x >= n) {
                        flag = false;
                        break;
                    }
                    for (int cnt = 2; cnt <= x; cnt++) {
                        if (map[ny + 1][nx] != map[ny + cnt][nx] || used[ny + cnt][nx]) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) break;
                    for (int cnt = 1; cnt <= x; cnt++)
                        used[ny + cnt][nx] = true;
                    ny += x - 1;
                }
            }
            if (flag)
                ans++;
        }
        cout << "#" << test_case << " " << ans << "\n";
        ans = 0;
    }
    return 0;
}
//used를 사용하지 않고 cnt만을 사용하여 구현
//한칸 내리막길일 경우, x만큼의 길이 필요
//한칸 오르막일 경우, 이전에 x만큼의 길이 필요
/*
#include <iostream>
using namespace std;
int ans, n, x;
int map[20][20];
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int test_case;
    int T, num, dir;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        cin >> n >> x;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> map[i][j];
        for (int i = 0; i < n; i++) {
            int cnt = 1;
            for (int j = 1; j < n; j++) {
                int prev = map[i][j - 1], cur = map[i][j];
                if (prev == cur)
                    cnt++;
                else if (prev - cur == 1 && cnt >= 0)
                    cnt = 1 - x;
                else if (prev - cur == -1 && cnt >= x)
                    cnt = 1;
                else {
                    cnt = -1;
                    break;
                }
            }
            if (cnt >= 0) ans++;
        }
        for (int j = 0; j < n; j++) {
            int cnt = 1;
            for (int i = 1; i < n; i++) {
                int prev = map[i - 1][j], cur = map[i][j];
                if (prev == cur)
                    cnt++;
                else if (prev - cur == 1 && cnt >= 0)
                    cnt = 1 - x;
                else if (prev - cur == -1 && cnt >= x)
                    cnt = 1;
                else {
                    cnt = -1;
                    break;
                }
            }
            if (cnt >= 0) ans++;
        }
        cout << "#" << test_case << " " << ans << "\n";
        ans = 0;
    }
    return 0;
}
*/