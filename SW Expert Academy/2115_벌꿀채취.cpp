#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <cstring>
using namespace std;
//Info.maxhoney = (y, x)좌표부터 m만큼 추출할 수 있는 최대 꿀의 양
struct Info {
    int y, x, maxhoney;
};
int board[10][10], visit[10];
int n, m, c, ans, temp;
vector<Info> honey;
deque<int> dq;
//꿀 채취할 수 있으면 true
bool canTakeHoney(Info a, Info b)
{
    if (a.y != b.y) return true;
    if (a.x < b.x && a.x + m - 1 < b.x) return true;
    if (a.x > b.x && b.x + m - 1 < a.x) return true;
    return false;
}
//temp = dq에 대해서 최대로 채취할 수 있는 꿀의 양
void findMaxHoney(int idx, int sum, int mulsum)
{
    temp = max(temp, mulsum);
    for (int i = idx; i < m; i++) {
        if (visit[i]) continue;
        if (sum + dq[i] > c) continue;
        visit[i] = true;
        sum += dq[i];
        mulsum += dq[i] * dq[i];
        findMaxHoney(i + 1, sum, mulsum);
        sum -= dq[i];
        mulsum -= dq[i] * dq[i];
        visit[i] = false;
    }
}
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        cin >> n >> m >> c;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> board[i][j];
        //deque를 사용하여 m만큼 벌통을 선택하였을 때 채취 가능한 꿀을 구함
        for (int i = 0; i < n; i++) {
            dq.clear();
            for (int j = 0; j < n; j++) {
                dq.push_back(board[i][j]);
                if (dq.size() > m)
                    dq.pop_front();
                if (dq.size() == m) {
                    temp = 0;
                    memset(visit, false, sizeof(visit));
                    findMaxHoney(0, 0, 0);
                    honey.push_back({ i, j, temp });
                }
            }
        }
        //모든 조합 가능한 꿀의 합에서 max값 구함
        for (int i = 0; i < honey.size(); i++)
            for (int j = i + 1; j < honey.size(); j++) {
                if (canTakeHoney(honey[i], honey[j])) {
                    ans = max(ans, honey[i].maxhoney + honey[j].maxhoney);
                }
            }
        cout << "#" << test_case << " " << ans << "\n";
        honey.clear();
        ans = 0;
    }
    return 0;
}