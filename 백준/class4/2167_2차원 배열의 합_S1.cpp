#include <iostream>
using namespace std;

int arr[300][300];
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, k;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> arr[i][j];
	cin >> k;
	while (k--) {
		int i, j, x, y, ans = 0;
		cin >> i >> j >> x >> y;
		for (int a = i; a <= x; a++)
			for (int b = j; b <= y; b++)
				ans += arr[a - 1][b - 1];
		cout << ans << endl;
	}
}