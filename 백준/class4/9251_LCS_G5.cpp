#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int dp[1001][1001];
int main()
{
	string str1, str2;
	cin >> str1 >> str2;
	str1 = ' ' + str1, str2 = ' ' + str2;
	for (int i = 0; i < str1.size(); i++) {
		for (int j = 0; j < str2.size(); j++) {
			if (i == 0 || j == 0) continue;
			if (str1[i] == str2[j])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	cout << dp[str1.size() - 1][str2.size() - 1];
}