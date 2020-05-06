#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(string s) {
    int answer = 0, len = s.size();
    answer = len;
    //1 ~ 문자열 길이만큼 탐색
    for (int i = 1; i < len; i++) {
        queue<string> q;
        //s를 i만큼씩 잘라서 queue에 넣기
        for (int idx = 0; idx < len; ) {
            string temp;
            for (int j = 0; j < i && idx < len; j++, idx++)
                temp += s[idx];
            q.push(temp);
        }
        //curlen = 현재 압축된 문자열 길이
        int curlen = 0;
        while (!q.empty()) {
            string cur = q.front();
            q.pop();
            int cnt = 1;
            //queue의 다음 문자열이 현재와 같으면, cnt++
            while (!q.empty() && q.front() == cur) {
                cnt++;
                q.pop();
            }
            //문자열 압축 안되면
            if (cnt == 1)
                curlen += cur.size();
            else
                curlen += to_string(cnt).size() + cur.size();
        }
        answer = min(answer, curlen);
    }    
    return answer;
}
int main()
{
    string s = "ababcdcdababcdcd";
    cout << solution(s);
}