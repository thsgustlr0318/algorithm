#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
bool cmp(const string& a, const string& b)
{
	return a + b > b + a;
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int n, k;
	string ans, input;
	vector<string> v;
	cin >> k >> n;
	for (int i = 0; i < k; i++) {
		cin >> input;
		v.push_back(input);
	}
	sort(v.begin(), v.end(), cmp);
	//maxv = 가장 길고 큰 수
	long long maxv = stoll(v[0]);
	for (int i = 1; i < k; i++)
		maxv = max(maxv, stoll(v[i]));
	//flag = maxv가 중복될 수 있으므로 중복 제거용도
	bool flag = false;
	for (int i = 0; i < k; i++) {
		if (stoll(v[i]) == maxv && !flag) {
			for (int j = 0; j < n - k; j++)
				cout << v[i];
			flag = true;
		}
		cout << v[i];
	}
	return 0;
}