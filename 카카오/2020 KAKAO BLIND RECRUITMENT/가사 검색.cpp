#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;
vector<string> v[10001], vr[10001];
//이분 탐색
//정확성, 효율성 모두 통과
vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;   
    int wsize = words.size(), qsize = queries.size();
    answer.resize(qsize);
    //단어 길이에 따라 v와 vr(reverse)에 단어 넣음
    for (int i = 0; i < wsize; i++) {
        int len = words[i].size();
        v[len].push_back(words[i]);
        reverse(words[i].begin(), words[i].end());
        vr[len].push_back(words[i]);
    }
    //v, vr 정렬
    for (int i = 1; i <= 10000; i++) {
        if(!v[i].empty())
            sort(v[i].begin(), v[i].end());
        if(!vr[i].empty())
            sort(vr[i].begin(), vr[i].end());
    }
    //모든 queries 단어 탐색
    for (int i = 0; i < qsize; i++) {
        string cur = queries[i];
        int len = cur.size();
        bool flag = true;
        //만약 ?가 접두사에 오면
        if (queries[i][0] == '?') {
            flag = false;
            reverse(cur.begin(), cur.end());
        }
        string low = cur, upp = cur;
        //low: ?를 a로, upp: ?를 z로
        //lower_bound와 upper_bound로 이분탐색
        replace(low.begin(), low.end(), '?', 'a');
        replace(upp.begin(), upp.end(), '?', 'z');
        if (flag) {
            auto it1 = lower_bound(v[len].begin(), v[len].end(), low);
            auto it2 = upper_bound(v[len].begin(), v[len].end(), upp);
            answer[i] = distance(v[len].begin(), it2) - distance(v[len].begin(), it1);
        }
        else {
            auto it1 = lower_bound(vr[len].begin(), vr[len].end(), low);
            auto it2 = upper_bound(vr[len].begin(), vr[len].end(), upp);
            answer[i] = distance(vr[len].begin(), it2) - distance(vr[len].begin(), it1);
        }
    }
    return answer;
}
int main()
{
    vector<string> words = { "frodo", "front", "frost", "frozen", "frame", "kakao" };
    vector<string> queries = {"fro??", "????o", "fr???", "fro???", "pro?"};
    solution(words, queries);
}
//unordered_map
//정확성 통과, 효율성 3개 통과
/*
vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    unordered_map<string, int> m;
    int wordsize = words.size(), querysize = queries.size();
    answer.resize(querysize);
    for (int i = 0; i < wordsize; i++) {
        string cur = words[i];
        int len = words[i].size();
        string temp = cur;
        m[cur]++;
        for (int i = 0; i < len; i++) {
            temp[i] = '?';
            m[temp]++;
        }
        temp = cur;
        for (int i = len - 1; i > 0; i--) {
            temp[i] = '?';
            m[temp]++;
        }
    }
    for (int i = 0; i < querysize; i++) {
        answer[i] = m[queries[i]];
    }
    return answer;
}
}*/