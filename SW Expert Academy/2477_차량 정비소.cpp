#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
struct Info {
    int num, time;
};
int ans, n, m, k, a, b;
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        cin >> n >> m >> k >> a >> b;
        int receptTime[9], repairTime[9], cnt = 0;
        Info receptUse[9], repairUse[9];
        queue<Info> customer, receptWait, repairWait;
        vector<int> v;
        for (int i = 0; i < 9; i++) {
            receptUse[i] = { 0, 0 };
            repairUse[i] = { 0, 0 };
        }
        for (int i = 0; i < n; i++)
            cin >> receptTime[i];
        for (int j = 0; j < m; j++)
            cin >> repairTime[j];
        for (int i = 1; i <= k; i++) {
            int t;
            cin >> t;
            customer.push({ i, t });
        }        
        for (int time = 0; cnt != k; time++) {
            //고객이 차량 정비소 도착하면, 접수 대기로 옮기기
            while (!customer.empty() && customer.front().time == time) {
                receptWait.push(customer.front());
                customer.pop();
            }
            //접수가 끝났으면, 정비 대기로 옮기기
            for (int i = 0; i < n; i++) {
                if (receptUse[i].time == receptTime[i]) {
                    repairWait.push(receptUse[i]);
                    receptUse[i] = { 0, 0 };
                }
            }
            //접수 창구가 비어 있으면 접수 대기->접수 창구
            for (int i = 0; i < n && !receptWait.empty(); i++) {
                if (receptUse[i].num) continue;
                receptUse[i] = { receptWait.front().num, 0 };
                receptWait.pop();
                if (i + 1 == a)
                    v.push_back(receptUse[i].num);
            }
            //정비 끝났으면, 확인 후 삭제
            for (int i = 0; i < m; i++) {
                if (repairUse[i].time == repairTime[i]) {
                    if (i + 1 == b) {
                        if (find(v.begin(), v.end(), repairUse[i].num) != v.end()) {
                            ans += repairUse[i].num;
                            v.erase(find(v.begin(), v.end(), repairUse[i].num));
                        }
                    }
                    repairUse[i] = { 0, 0 };
                    cnt++;
                }
            }
            //정비 창구 비어 있으면 정비 대기->정비 창구
            for (int i = 0; i < m && !repairWait.empty(); i++) {
                if (repairUse[i].num) continue;
                repairUse[i] = { repairWait.front().num, 0 };
                repairWait.pop();
            }
            //시간 증가
            for (int i = 0; i < n; i++) 
                if (receptUse[i].num) receptUse[i].time++;           
            for (int i = 0; i < m; i++) 
                if (repairUse[i].num) repairUse[i].time++;            
        }
        if (ans == 0) ans = -1;
        cout << "#" << test_case << " " << ans << "\n";
        ans = 0;
    }
    return 0;
}