#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
bool cmp(pair<float, int>& a, pair<float, int>& b) {
    if (a.first == b.first)
        return a < b;
    return a.first > b.first;
}
vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<int> visited(N + 1, 0), noclear(N + 1, 0);
    vector<pair<float, int>> fail(N + 1);
    for (int i = 0; i < stages.size(); i++) {
        if(stages[i] != N+1)
            noclear[stages[i]]++;
        for (int j = 1; j <= stages[i] && j <= N; j++)
            visited[j]++;
    }
    for (int i = 1; i <= N; i++) {
        if (visited[i] == 0)
            fail[i].first = 0;
        else
            fail[i].first = (float)noclear[i] / (float)visited[i];
        fail[i].second = i;
    }
    sort(fail.begin(), fail.end(), cmp);
    answer.resize(N);
    for (int i = 0, idx = 0; i < fail.size(); i++) {
        if (fail[i].second == 0) continue;
        answer[idx++] = fail[i].second;
    }
    return answer;
}
int main()
{
    int n = 5;
    vector<int> stages = { 2, 1, 2, 6, 2, 4, 3, 3 };
    vector<int> ans = solution(n, stages);
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
}