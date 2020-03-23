#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int ans, k;
int saw[4][8];
bool check[4];
void f(int idx, int dir)
{
	check[idx] = true;
	if (idx < 3 && !check[idx + 1] && saw[idx][2] != saw[idx + 1][6])
		f(idx + 1, -dir);
	if (idx > 0 && !check[idx - 1] && saw[idx][6] != saw[idx - 1][2])
		f(idx - 1, -dir);
	if (dir == 1)
		rotate(saw[idx], saw[idx] + 7, saw[idx] + 8);
	else
		rotate(saw[idx], saw[idx] + 1, saw[idx] + 8);
}
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int test_case;
	int T, num, dir;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> k;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 8; j++)
				cin >> saw[i][j];
		for (int i = 0; i < k; i++) {
			cin >> num >> dir;
			f(num - 1, dir);
			memset(check, false, sizeof(check));
		}
		for (int i = 0; i < 4; i++)
			ans += saw[i][0] << i;
		cout << "#" << test_case << " " << ans << "\n";
		ans = 0;
	}
	return 0;
}