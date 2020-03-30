#include <iostream>
#include <algorithm>
using namespace std;
int ans;
int month[12], price[4];
void dfs(int idx, int sum)
{
    if (idx >= 12) {
        ans = min(ans, sum);
        return;
    }
    //해당 달의 이용횟수가 없으면, 다음 달 확인
    if (month[idx] == 0)
        dfs(idx + 1, sum);
    //3개월 이용권
    dfs(idx + 3, sum + price[2]);
    //1개월 이용권
    dfs(idx + 1, sum + price[1]);
    //일일권
    dfs(idx + 1, sum + price[0] * month[idx]);
}
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        for (int i = 0; i < 4; i++)
            cin >> price[i];
        for (int i = 0; i < 12; i++)
            cin >> month[i];
        //12개월 이용권
        ans = price[3];
        dfs(0, 0);
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;
}