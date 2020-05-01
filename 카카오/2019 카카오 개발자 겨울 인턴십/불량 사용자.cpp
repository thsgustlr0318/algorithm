#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool user_check[8];
int ans = 0;
bool checkBanYes(string& s1, string& s2)
{
    if (s1.size() != s2.size())
        return false;
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] == '*' || s2[i] == '*') continue;
        if (s1[i] != s2[i]) return false;
    }
    return true;
}
void dfs(int cnt, vector<vector<int>> v, vector<int>& checkhis)
{
    if (cnt == v.size()) {
        int temp = 0;
        for (int i = 0; i < 8; i++)
            if (user_check[i])
                temp |= (1 << i);
        for (int i = 0; i < checkhis.size(); i++)
            if (temp == checkhis[i]) return;
        checkhis.push_back(temp);
        ans++;
        return;
    }
    for (int i = 0; i < v[cnt].size(); i++) {
        if (user_check[v[cnt][i]]) continue;
        user_check[v[cnt][i]] = true;
        dfs(cnt + 1, v, checkhis);
        user_check[v[cnt][i]] = false;
    }
}
int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    vector<vector<int>> v;
    vector<int> checkhis;
    for (int i = 0; i < banned_id.size(); i++) {
        vector<int> tmp;
        for (int j = 0; j < user_id.size(); j++)
            if (checkBanYes(banned_id[i], user_id[j]))
                tmp.push_back(j);
        v.push_back(tmp);
    }
    dfs(0, v, checkhis);
    answer = ans;
    return answer;
}
int main()
{
    vector<string> v1 = { "frodo", "fradi", "crodo", "abc123", "frodoc" };
    vector<string> v2 = { "fr*d*", "*rodo", "******", "******" };
    cout << solution(v1, v2);
}