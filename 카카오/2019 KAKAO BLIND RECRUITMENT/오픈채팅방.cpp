#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;
struct userInfo {
    //0: Enter, 1: Leave, 2: Change
    int state;
    string id, nickname;
};
vector<string> solution(vector<string> record) {
    vector<string> answer;
    vector<pair<int, userInfo>> command;
    map<string, string> user;
    queue<userInfo> q;
    for (int i = 0; i < record.size(); i++) {
        string cur = record[i];
        userInfo u;
        int idx = 0, idx2;
        if (cur.substr(0, 5).compare("Enter") == 0) {
            u.state = 0;
            idx = 6;
        }
        else if (cur.substr(0, 5).compare("Leave") == 0) {
            u.state = 1;
            idx = 6;
            u.id = cur.substr(idx, cur.size() - idx);
        }
        else {
            u.state = 2;
            idx = 7;
        }
        //Leave�� ���
        if (u.state == 1) {
            q.push(u);
            continue;
        }
        //���̵�, �г��� ã��
        for (idx2 = idx; cur[idx2] != ' '; idx2++);
        u.id = cur.substr(idx, idx2 - idx);
        u.nickname = cur.substr(idx2 + 1, cur.size() - idx2 + 1);
        //Enter, Change�� ��� map ����
        user[u.id] = u.nickname;
        //Enter�� ���, queue�� ����
        if(u.state==0)
            q.push(u);
    }
    while (!q.empty()) {
        userInfo cur = q.front();
        q.pop();
        if (cur.state == 0)
            answer.push_back(user[cur.id] + "���� ���Խ��ϴ�.");
        else
            answer.push_back(user[cur.id] + "���� �������ϴ�.");
    }
    return answer;
}
int main()
{
    vector<string> record = { "Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan" };
    vector<string> ans = solution(record);
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << "\n";
}