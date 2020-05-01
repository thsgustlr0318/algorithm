#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//HH:MM -> 분
int convertMinute(string str) {
    return stoi(str.substr(0, 2)) * 60 + stoi(str.substr(3, 2));
}
//분 -> HH:MM
string convertTime(int num) {
    string temp;
    string hour = to_string(num / 60), minute = to_string(num % 60);
    if (hour.size() == 1)
        hour = "0" + hour;
    if (minute.size() == 1)
        minute = "0" + minute;
    return hour + ":" + minute;
}
string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
    int len = timetable.size();
    vector<int> time(len);
    //모든 HH:MM을 '분'으로 바꿔서 time에 넣음
    for (int i = 0; i < len; i++)
        time[i] = convertMinute(timetable[i]);
    sort(time.begin(), time.end());
    int busTime = 540;
    int idx = 0;
    //마지막 버스 전까지의 idx와, 버스 출발 시간 구함
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (busTime >= time[idx])
                idx++;
            else
                break;
        }
        busTime += t;
    }
    //다음으로 타는 사람의 시간이 버스 출발시간보다 늦을 때
    if (time[idx] > busTime)
        return convertTime(busTime);
    //마지막에 타더라도 버스에 탈 수 있을 때
    if (idx + m > len)
        return convertTime(busTime);
    //버스 마지막에 타는 사람보다 1분 일찍 출발하면 버스 탈 수 있음
    return convertTime(time[idx + m - 1] - 1);
}
int main()
{
    int n = 2, t = 10, m = 2;
    vector<string> timetable = { "09:10", "09:09", "08:00" };
    cout << solution(n, t, m, timetable);
}