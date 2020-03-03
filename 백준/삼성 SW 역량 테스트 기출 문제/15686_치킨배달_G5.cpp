#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;
int n, m, arr[50][50], result = 2e9;
int distance(int y1, int x1, int y2, int x2)
{
	return abs(y2 - y1) + abs(x2 - x1);
}
void dfs(int cnt, int y)
{
	if (cnt == m) {
		vector<pair<int, int>> home, chicken;
		int ans = 0, temp;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (arr[i][j] == 1)
					home.push_back(make_pair(i, j));
				else if (arr[i][j] == 2)
					chicken.push_back(make_pair(i, j));
			}
		for (int i = 0; i < home.size(); i++) {
			temp = 2e9;
			for (int j = 0; j < chicken.size(); j++) {
				temp = min(temp, distance(home[i].first, home[i].second, chicken[j].first, chicken[j].second));
			}
			ans += temp;
		}
		result = min(ans, result);
		return;
	}
	for (int i = y; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == 2) {
				arr[i][j] = 0;
				dfs(cnt - 1, i);
				arr[i][j] = 2;
			}
		}
}
int main()
{
	int chick = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2)
				chick++;
		}
	dfs(chick, 0);
	cout << result;
}