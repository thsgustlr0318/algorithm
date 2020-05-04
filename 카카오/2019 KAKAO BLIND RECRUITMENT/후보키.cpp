#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
//used = 속성이 사용되었는지 확인
//history = 후보키 비트마스크 값
vector<int> used, history;
void dfs(vector<vector<string>>& relation, int size, int idx) {
    int row = relation.size(), col = relation[0].size();
    if (size >= 2) {
        set<string> s;
        for (int i = 0; i < row; i++) {
            string temp;
            for (int j = 0; j < col; j++) {
                if (used[j] == 1)
                    temp += relation[i][j];
            }
            s.insert(temp);
        }
        //후보키
        if (s.size() == relation.size()) {
            int num = 0;
            for (int i = 0; i < col; i++) {
                if (used[i] == 1)
                    num |= 1;
                num = num << 1;
            }
            num = num >> 1;
            history.push_back(num);
        }
    }
    for (int i = idx; i < col; i++) {
        if (used[i] == 2 || used[i] == 1) continue;
        used[i] = 1;
        dfs(relation, size + 1, i + 1);
        used[i] = 0;
    }
}
int solution(vector<vector<string>> relation) {
    int answer = 0;
    int row = relation.size(), col = relation[0].size();
    //key = 중복되는 튜플이 있는 키
    vector<int> key;
    used.resize(col);
    //크기가 1인 후보키 찾기
    for (int i = 0; i < col; i++) {
        set<string> s;
        for (int j = 0; j < row; j++) 
            s.insert(relation[j][i]);        
        if (s.size() == row) {
            answer++;
            used[i] = 2;
        }
        else
            key.push_back(i);
    }
    //중복되는 속성들 모두 탐색
    dfs(relation, 0, 0);
    //history = 후보키들 비트마스크 값
    sort(history.begin(), history.end());
    //후보키 최소성 찾기
    vector<bool> check(history.size(), 0);
    for (int i = 0; i < history.size(); i++) {
        if (check[i]) continue;
        for (int j = i + 1; j < history.size(); j++) {
            if (check[j]) continue;
            if ((history[i] & history[j]) == history[i])
                check[j] = true;
        }
    }
    for (int i = 0; i < history.size(); i++)
        if (!check[i]) answer++;
    return answer;
}
int main()
{
    vector<vector<string>> relation = { {"100", "ryan", "music", "2"} ,{"200", "apeach", "math", "2"},{"300", "tube", "computer", "3"},{"400", "con", "computer", "4"},{"500", "muzi", "music", "3"},{"600", "apeach", "music", "2"} };
    cout << solution(relation);
}