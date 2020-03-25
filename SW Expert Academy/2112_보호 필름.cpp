#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int film[13][20];
int ans, d, w, k;
int visit[13];
//검사 통과: true
bool checkPass()
{
    bool flag = false;
    for (int j = 0; j < w; j++) {
        int cnt = 1;
        flag = false;
        for (int i = 1; i < d && !flag; i++) {
            film[i - 1][j] == film[i][j] ? cnt++ : cnt = 1;
            if (cnt >= k) flag = true;
        }
        if (!flag) break;
    }
    return flag;
}
void dfs(int cnt, int idx, int inputcnt)
{
    if (cnt == inputcnt) {
        if (checkPass()) 
            ans = min(ans, cnt);        
        return;
    }
    for (int i = idx; i < d; i++) {
        //ab=1: a약물 투입, ab=2: b약물 투입
        for (int ab = 1; ab <= 2; ab++) {
            if (visit[i]) continue;
            int temp[13][20];
            memcpy(temp, film, sizeof(film));
            visit[i] = ab;
            //해당 막(i)에 약물 투입(ab-1)
            for (int j = 0; j < w; j++)
                film[i][j] = ab - 1;
            //다음막부터 탐색
            dfs(cnt + 1, i + 1, inputcnt);
            memcpy(film, temp, sizeof(film));
            visit[i] = 0;
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
        cin >> d >> w >> k;
        ans = 2e9;
        for (int i = 0; i < d; i++)
            for (int j = 0; j < w; j++)
                cin >> film[i][j];
        //0 ~ k전까지 탐색
        for (int i = 0; i < k && ans == 2e9; i++)
            dfs(0, 0, i);
        //ans == 2e9면, 성능검사를 통과 못했으므로, 최대 투입 횟수인 k 출력
        if (ans == 2e9) ans = k;
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;
}