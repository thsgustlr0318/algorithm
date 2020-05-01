#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
map<long long, long long> m;
long long getParent(long long num)
{
	if (m[num] == 0) {
		m[num] = num + 1;
		return num;
	}
	return m[num] = getParent(m[num]);
}
vector<long long> solution(long long k, vector<long long> room_number) {
	vector<long long> answer;
	for (int i = 0; i < room_number.size(); i++) {
		answer.push_back(getParent(room_number[i]));
	}
	return answer;
}
int main()
{
    int k = 10;
    vector<long long> room_number = { 1, 3, 4, 1, 3, 1 };
    vector<long long> result = solution(k, room_number);
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
}