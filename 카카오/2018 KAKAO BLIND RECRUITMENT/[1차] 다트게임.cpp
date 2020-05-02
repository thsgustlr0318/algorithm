#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct scoreInfo {
    int score;
    char bonus, option;
};
int solution(string dartResult) {
    int answer = 0;
    vector<int> score(3, 0);
    vector<scoreInfo> si;
    for (int cnt = 0, idx = 0; idx < dartResult.size();) {
        int num = 0;
        for (; 0 <= dartResult[idx] - '0' && dartResult[idx] - '0' <= 9; idx++, num *= 10) 
            num += dartResult[idx] - '0';        
        num /= 10;
        char b = dartResult[idx++];
        char o = NULL;
        if (dartResult[idx] == '*' || dartResult[idx] == '#')
            o = dartResult[idx++];
        si.push_back({ num, b, o });       
    }
    //보너스에 따른 점수 (S, D, T)
    for (int i = 0; i < 3; i++) {
        if (si[i].bonus == 'D')
            score[i] = si[i].score * si[i].score;
        else  if (si[i].bonus == 'T')
            score[i] = si[i].score * si[i].score * si[i].score;
        else
            score[i] = si[i].score;
    }
    //아차상
    for (int i = 0; i < 3; i++)
        if (si[i].option == '#')
            score[i] *= -1;
    //스타상
    for (int i = 0; i < 3; i++) {
        if (si[i].option == '*') {
            score[i] *= 2;
            if (i != 0)
                score[i - 1] *= 2;
        }
    }
    answer = score[0] + score[1] + score[2];
    return answer;
}
int main() 
{
    string dartResult = "1S2D*3T";
    cout << solution(dartResult);
}