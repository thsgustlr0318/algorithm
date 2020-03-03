#include <iostream>
#include <algorithm>
using namespace std;

int n, m, h, ans = 4;
bool arr[31][11];

bool check()
{
	for (int x = 1; x <= n; x++) {
		int nx = x;
		for (int ny = 1; ny <= h; ny++) {
			if (arr[ny][nx])
				nx++;
			else if (nx > 0 && arr[ny][nx - 1])
				nx--;
		}
		if (x != nx)
			return false;
	}
	return true;
}

void dfs(int cnt, int idx)
{
	if (ans <= cnt || cnt > 3)
		return;
	if (check()) {
		ans = min(ans, cnt);
		return;
	}
	int y = idx / n + 1, x;
	for (; y <= h; y++)
		for (x = 1; x < n; x++) {
			if (arr[y][x])
				x++;
			else {
				if (arr[y][x + 1] == false) {
					arr[y][x] = true;
					dfs(cnt + 1, (y - 1) * n + x);
					arr[y][x] = false;
				}
			}
		}
}
int main()
{
	cin >> n >> m >> h;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		arr[a][b] = true;
	}
	dfs(0, 1);
	ans == 4 ? cout << "-1" : cout << ans;
}