#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    //첫번째 지도
    for (int i = 0; i < n; i++) {
        int cur = arr1[i];
        string str;
        for (int j = 0; j < n; j++) {
            if (cur & 1)
                str = '#' + str;
            else
                str = ' ' + str;
            cur = cur >> 1;
        }
        answer.push_back(str);
    }
    //두번째 지도
    for (int i = 0; i < n; i++) {
        int cur = arr2[i];
        for (int j = n - 1; j >= 0; j--) {
            if (cur & 1)
                answer[i][j] = '#';
            cur = cur >> 1;
        }
    }
    return answer;
}
int main()
{
    int n = 5;
    vector<int> arr1 = { 9, 20, 28, 18, 11 };
    vector<int> arr2 = { 30, 1, 21, 17, 28 };
    vector<string> ans = solution(n, arr1, arr2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << ans[i][j];
        cout << "\n";
    }
}