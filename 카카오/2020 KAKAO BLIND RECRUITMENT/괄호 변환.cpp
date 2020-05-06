#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
bool check(string str) {
    if (str == "") return true;
    stack<int> s;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '(') s.push(1);
        else {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return true;
}
string calc(string str) {
    //1
    if (str == "") return "";
    int left = 0, right = 0, idx = 1;
    //2) u, v 분리
    if (str[0] == '(') left++;
    else right++;
    while (left != right) {
        if (str[idx] == '(') left++;
        else right++;
        idx++;
    }
    string u = str.substr(0, idx), v;
    for (int i = idx; i < str.size(); i++) v += str[i];
    //3
    if (check(u))
        return u + calc(v);
    //4-1, 4-2, 4-3
    string temp = "(" + calc(v) + ")";
    //4-4
    for (int i = 1; i < u.size() - 1; i++) {
        if (u[i] == '(') temp += ")";
        else temp += "(";
    }
    //4-5
    return temp;
}
string solution(string p) {
    string answer = "";
    answer = calc(p);
    return answer;
}
int main()
{
    string p = "(()())()";
    cout << solution(p);
}