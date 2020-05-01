#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
struct timeInfo {
    int start, end;
};
timeInfo getTimeData(string str) {
    timeInfo data;
    string t, end;
    data.end = stoi(str.substr(11, 2)) * 3600 * 1000 + stoi(str.substr(14, 2)) * 60 * 1000 + stoi(str.substr(17, 2)) * 1000 + stoi(str.substr(20, 3));
    t = str.substr(24, str.length() - 2);
    int temp = (int)(stof(t) * 1000);
    data.start = data.end - temp + 1;
    return data;
}
int solution(vector<string> lines) {
    int answer = 0, len = lines.size();;
    vector<long long> start(len), end(len);
    for (int i = 0; i < len; i++) {
        timeInfo temp = getTimeData(lines[i]);
        start[i] = temp.start, end[i] = temp.end;
    }
    for (int i = 0; i < len; i++) {
        int cnt = 0;
        for (int j = 0; j < len; j++) {
            if ((start[i] <= start[j] && start[j] < start[i] + 1000) || (start[i] <= end[j] && end[j] < start[i] + 1000) || (start[j]<=start[i] && start[i]+1000 < end[j]))
                cnt++;
        }
        answer = max(answer, cnt);
        cnt = 0;
        for (int j = 0; j < len; j++) {
            if ((end[i] <= start[j] && start[j] < end[i] + 1000) || (end[i] <= end[j] && end[j] < end[i] + 1000) || (start[j] <= end[i] && end[i] + 1000 < end[j]))
                cnt++;
        }
        answer = max(answer, cnt);
    }
    return answer;
}
int main()
{
    vector<string> lines = {
"2016-09-15 01:00:04.002 2.0s", "2016-09-15 01:00:07.000 2s" };
    cout << solution(lines);
}