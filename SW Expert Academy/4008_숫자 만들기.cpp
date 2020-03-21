#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int n, minv, maxv;
vector<int> nums, oper;
bool check[12];
void init()
{
	minv = 1e9, maxv = -1e9;
	nums.clear(), oper.clear();
	memset(check, false, sizeof(check));
}
int calc(int a, int b, int op)
{
	if (op == 1) return a + b;
	else if (op == 2) return a - b;
	else if (op == 3) return a * b;
	return a / b;
}
void dfs(int cnt, int sum)
{
	if (cnt == n - 1) {
		maxv = max(maxv, sum);
		minv = min(minv, sum);
		return;
	}
	int prev = 0;
	for (int idx = 0; idx < n - 1; idx++) {
		if (!check[idx] && prev != oper[idx]) {
			prev = oper[idx];
			check[idx] = true;
			dfs(cnt + 1, calc(sum, nums[cnt + 1], oper[idx]));
			check[idx] = false;
		}
	}
}
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		init();
		cin >> n;
		nums.resize(n);
		for (int i = 1; i <= 4; i++) {
			int opernum;
			cin >> opernum;
			for (int j = 0; j < opernum; j++)
				oper.push_back(i);
		}
		for (int i = 0; i < n; i++)
			cin >> nums[i];
		dfs(0, nums[0]);
		cout << "#" << test_case << " " << maxv - minv << "\n";
	}
	return 0;
}