#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//이분 탐색 이용한 방법
bool calc(vector<int>& stones, int k, int n) {
    int len = stones.size();
    int ans = 0;
    for (int i = 0; i < len; i++) {
        if (stones[i] - n <= 0)
            ans++;
        else
            ans = 0;
        if (ans >= k)
            return false;
    }
    return true;
}
int solution(vector<int> stones, int k) {
    int left = 1, right = 2e9;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (calc(stones, k, mid)) 
            left = mid + 1;        
        else
            right = mid - 1;
    }
    return left;
}
int main()
{
    vector<int> stones = { 3, 2, 1, 3, 2, 4, 4, 2 ,5 , 1, 5 };
    int k = 3;
    cout << solution(stones, k);
}
//k개의 수가 높은수->낮은수 순서로 있는 배열 중, 제일 낮은 값 찾기
/*
int solution(vector<int> stones, int k) {
    int answer = 0;
    auto len = stones.size();
    int maxv = 0;
    for (int i = 0; i < k; i++)
        maxv = max(maxv, stones[i]);
    answer = maxv;
    for (int left = 0, right = k; right < len; left++, right++) {
        if (maxv != stones[left])
            maxv = max(maxv, stones[right]);
        else {
            maxv = 0;
            for (int i = 0; i < k; i++)
                maxv = max(maxv, stones[right - i]);
        }
        answer = min(answer, maxv);
    }
    return answer;
}
*/