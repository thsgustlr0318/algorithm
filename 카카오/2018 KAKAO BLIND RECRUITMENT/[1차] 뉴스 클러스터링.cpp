#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
bool checkAlpha(string str, int idx) {
    if ('a' <= str[idx] && str[idx] <= 'z' && 'a' <= str[idx + 1] && str[idx + 1] <= 'z')
        return true;
    return false;
}
int solution(string str1, string str2) {
    int answer = 0;
    vector<string> v1, v2;
    for (int i = 0; i < str1.size(); i++)
        if ('A' <= str1[i] && str1[i] <= 'Z')
            str1[i] += 32;
    for (int i = 0; i < str2.size(); i++)
        if ('A' <= str2[i] && str2[i] <= 'Z')
            str2[i] += 32;
    for (int i = 0; i < str1.size() - 1; i++) 
        if (checkAlpha(str1, i))
            v1.push_back(str1.substr(i, 2));    
    for (int i = 0; i < str2.size() - 1; i++) 
        if (checkAlpha(str2, i))
            v2.push_back(str2.substr(i, 2));
    if (v1.empty() && v2.empty()) return 65536;
    //v1, v2 전부 확인하여 풀기
    float total_num = v1.size() + v2.size(), inter_num = 0;
    for (int i = 0; i < v1.size(); i++) {
        for (int j = 0; j < v2.size(); j++) {
            if (v1[i].compare(v2[j]) == 0) {
                inter_num++;
                v2.erase(v2.begin() + j);
                break;
            }
        }
    }
    total_num -= inter_num;
    answer = inter_num / total_num * 65536;
    //set_union과 set_intersection으로 풀기
    /*
    vector<string> s1, s2;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(s1));
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(s2));
    answer = ((float)s2.size() / (float)s1.size()) * 65536;
    */
    return answer;
}
int main()
{
    string str1 = "FRANCE";
    string str2 = "FRENCH";
    cout << solution(str1, str2);
}