#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
bool cmp(vector<int>& a, vector<int>& b) {
    return a.size() < b.size();
}
vector<int> solution(string s) {
    vector<int> answer;
    vector<vector<int>> v;
    vector<bool> check(100001, false);
    for (int i = 0; i < s.size(); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            int temp = s[i++] - '0';
            vector<int> tv;
            while (1) {
                if ('0' <= s[i] && s[i] <= '9') {
                    temp *= 10;
                    temp += s[i] - '0';
                }
                else if (s[i] == ',') {
                    tv.push_back(temp);
                    temp = 0;
                }
                else if (s[i] == '}') {
                    tv.push_back(temp);
                    v.push_back(tv);
                    break;
                }
                i++;
            }
        }
    }
    sort(v.begin(), v.end(), cmp);
    answer.push_back(v[0][0]);
    check[v[0][0]] = true;
    for (int i = 1; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (check[v[i][j]]) continue;
            answer.push_back(v[i][j]);
            check[v[i][j]] = true;
        }
    }
    return answer;
}
int main()
{
    string str = "{{2},{2,1},{2,1,3},{2,1,3,4}}";
    vector<int> v = solution(str);
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
}