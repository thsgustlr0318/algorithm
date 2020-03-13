#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
long long ans = -5e9;
vector<long long> num;
vector<char> oper;
long long calc(long long a, long long b, char op)
{
	if (op == '+') return a + b;
	else if (op == '-') return a - b;
	return a * b;
}
void dfs(int idx, long long sum)
{
	if (idx == oper.size()) {
		ans = max(ans, sum);
		return;
	}
	//순서대로
	dfs(idx + 1, calc(sum, num[idx + 1], oper[idx]));
	//괄호 묶은경우
	//sum 'operator' temp(괄호 연산값)
	if (idx < oper.size() - 1) {
		long long temp = calc(num[idx + 1], num[idx + 2], oper[idx + 1]);
		dfs(idx + 2, calc(sum, temp, oper[idx]));
	}
}
int main()
{
	int n;
	string str;
	cin >> n >> str;
	for (int i = 0; i < str.size(); i++) {
		if ('0' <= str[i] && str[i] <= '9')
			num.push_back(str[i] - '0');
		else
			oper.push_back(str[i]);
	}
	dfs(0, num[0]);
	cout << ans;
}
//문제 범위값 잘보기
//-2^32 ~ 2^32