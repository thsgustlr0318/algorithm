#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int dp[1001][1001], ans;
int main()
{
	string str1, str2;
	cin >> str1 >> str2;
	str1 = " " + str1, str2 = " " + str2;
	for (int i = 0; i < str1.length(); i++)
		for (int j = 0; j < str2.length(); j++) {
			if (i == 0 || j == 0) continue;
			if (str1[i] == str2[j])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	ans = dp[str1.length() - 1][str2.length() - 1];
	cout << ans;
	if (ans != 0) {
		string temp;
		int y = str1.length() - 1, x = str2.length() - 1;
		while (dp[y][x] != 0) {
			if (dp[y - 1][x] == ans)
				y--;
			else if (dp[y][x - 1] == ans)
				x--;
			else {
				temp += str1[y];
				x--, y--, ans--;
			}
		}
		reverse(temp.begin(), temp.end());
		cout << "\n" << temp;
	}
}