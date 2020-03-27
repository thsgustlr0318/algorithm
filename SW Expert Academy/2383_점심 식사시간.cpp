#include <iostream>
#include <algorithm>
#include <queue>
#include <deque>
#include <vector>
#include <cstring>
using namespace std;
struct Info {
    int y, x;
};
//사람들, 계단 2개의 좌표
vector<Info> people, stairs;
int map[10][10];
int ans, n;
bool check[10];
//stair1, stair2를 이용하는 사람들 번호
vector<int> stair1, stair2;
void init()
{
    stair1.clear(), people.clear(), stairs.clear();
    ans = 2e9;
}
int calc(vector<int>& v, Info stairnum)
{
    int time = 0, cnt = v.size(), cost = map[stairnum.y][stairnum.x];
    vector<int> arrivetime;
    for (int i = 0; i < v.size(); i++)
        arrivetime.push_back(abs(stairnum.y - people[v[i]].y) + abs(stairnum.x - people[v[i]].x));
    sort(arrivetime.begin(), arrivetime.end());
    queue<int> wait;
    deque<int> usingstair;
    for (int idx = 0; cnt != 0; time++) {
        //도착하면, wait에 넣음
        while (idx < v.size() && arrivetime[idx] == time) {
            wait.push(arrivetime[idx]);
            idx++;
        }
        //계단을 다 내려간경우
        while (!usingstair.empty() && usingstair.front() == cost) {
            cnt--;
            usingstair.pop_front();
        }
        //기다리고 있으면서 계단을 다 사용 안하는 경우
        while (!wait.empty() && usingstair.size() < 3) {
            usingstair.push_back(0);
            wait.pop();
        }
        //시간 증가
        for (int i = 0; i < usingstair.size(); i++)
            usingstair[i]++;
    }
    return time;
}
void dfs(int idx, int cnt)
{
    //stair1을 사용하지 않는 경우, stair2에 넣기
    stair2.clear();
    for (int i = 0; i < people.size(); i++)
        if (!check[i]) stair2.push_back(i);
    //해당 경우의 소요시간 구하기
    int time = max(calc(stair1, stairs[0]), calc(stair2, stairs[1]));
    ans = min(ans, time);
    //stair1을 이용할 수 있는 모든 경우의 수
    for (int i = idx; i < people.size(); i++) {
        if (check[i]) continue;
        stair1.push_back(i);
        check[i] = true;
        dfs(i + 1, cnt + 1);
        check[i] = false;
        stair1.pop_back();
    }
}
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        init();
        cin >> n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> map[i][j];
                if (map[i][j] == 1) people.push_back({ i, j });
                else if (map[i][j] > 1) stairs.push_back({ i, j });
            }
        dfs(0, 0);
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;
}