#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int solution(vector<int> food_times, long long k) {
    int answer = 0;
    //v = food_times를 시간 순서로 정렬한 것
    vector<int> v(food_times);
    sort(v.begin(), v.end());
    long long prev = 0, cur = v[0], idx = 0, len = food_times.size();
    //v에서 작은 값부터 탐색
    while (1) {
        //중복되는 갯수 찾기
        int duplicate = 0;
        for (; idx != food_times.size() && cur == v[idx]; idx++, duplicate++);
        // k = k - v에서 이전 값과의 차이 * 남아 있는 음식값
        k -= (cur - prev) * len;
        len -= duplicate;
        //k가 0보다 작거나 혹은 v의 모든 값 탐색했을 경우
        if (k < 0 || idx == food_times.size()) {
            k += (cur - prev) * (len + duplicate);
            break;
        }
        prev = cur, cur = v[idx];
    }
    long long total = 0;
    vector<int> remain;
    //food_times에서 prev값보다 큰 것들 remain에 넣음
    for (idx = 0; idx < food_times.size(); idx++) {
        food_times[idx] -= prev;
        if (food_times[idx] > 0) {
            total += food_times[idx];
            remain.push_back(idx);
        }
    }
    //남아 있는 음식의 양 <= k인 경우, 더 섭취할 수 있는 음식 없음
    if (total <= k)
        return -1;
    answer = remain[k % remain.size()] + 1;
    return answer;
}
int main()
{
    vector<int> food_time = { 1, 3, 2 };
    long long k = 5;
    cout << solution(food_time, k);
}