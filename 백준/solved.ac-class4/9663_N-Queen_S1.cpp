#include <iostream>
#include <math.h>
using namespace std;

int col[15], ans, n;
bool check(int idx)
{
	for (int i = 0; i < idx; i++) {
		if (col[i] == col[idx] || abs(col[i] - col[idx]) == (idx - i))
			return false;
	}
	return true;
}
void dfs(int idx)
{
	if (idx == n) {
		ans++;
		return;
	}
	for (int i = 0; i < n; i++) {
		col[idx] = i;
		if (check(idx))
			dfs(idx + 1);
	}
}
int main()
{
	cin >> n;
	dfs(0);
	cout << ans;
}