#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
struct info {
	int r = 0, c = 0, s = 0;
};
vector<info> v, command;
int arr[51][51];
bool visit[6];
int n, m, k, ans = 2e9;
void rotate(int r, int c, int s)
{
	int temp[51][51];
	memcpy(temp, arr, sizeof(arr));
	for (int i = s; i > 0; i--) {
		for (int y = r - i, x = c - i + 1; x <= c + i; x++)
			arr[y][x] = temp[y][x - 1];
		for (int y = r - i + 1, x = c + i; y <= r + i; y++)
			arr[y][x] = temp[y - 1][x];
		for (int y = r + i, x = c + i - 1; x >= c - i; x--)
			arr[y][x] = temp[y][x + 1];
		for (int y = r + i - 1, x = c - i; y >= r - i; y--)
			arr[y][x] = temp[y + 1][x];
	}
}
void dfs(int cnt)
{
	if (cnt == k) {
		int temp[51][51];
		memcpy(temp, arr, sizeof(arr));
		int min_row = 2e9;
		for (int i = 0; i < k; i++)
			rotate(command[i].r, command[i].c, command[i].s);
		for (int i = 1; i <= n; i++) {
			int row = 0;
			for (int j = 1; j <= m; j++)
				row += arr[i][j];
			min_row = min(row, min_row);
		}
		ans = min(ans, min_row);
		memcpy(arr, temp, sizeof(arr));
		return;
	}
	for (int i = 0; i < k; i++) {
		if (visit[i]) continue;
		visit[i] = true;
		command.push_back(v[i]);
		dfs(cnt + 1);
		visit[i] = false;
		command.pop_back();
	}
}
int main()
{
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> arr[i][j];
	v.resize(k);
	for (int i = 0; i < k; i++) 
		cin >> v[i].r >> v[i].c >> v[i].s;
	dfs(0);
	cout << ans;
}