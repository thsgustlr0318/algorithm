#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;
    int len = cities.size();
    //cache 없을 경우
    if (cacheSize == 0)
        return 5 * len;
    //cities 소문자로 변환
    for (int i = 0; i < len; i++)
        transform(cities[i].begin(), cities[i].end(), cities[i].begin(), ::tolower);
    vector<string> cache;
    //모든 cache 확인
    for (int idx = 0; idx < len; idx++) {
        auto cache_it = find(cache.begin(), cache.end(), cities[idx]);
        if (cache_it == cache.end()) {
            answer += 5;
            if (cache.size() == cacheSize)
                cache.erase(cache.begin());
        }
        else {
            answer += 1;
            cache.erase(cache_it);
        }
        cache.push_back(cities[idx]);
    }
    return answer;
}
int main()
{
    int cacheSize = 3;
    vector<string> cities = { "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul" };
    cout << solution(cacheSize, cities);
}