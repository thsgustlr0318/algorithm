#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int food[16][16];
int n, ans;
bool check[16];
vector<int> a, b;
int calc(vector<int>& v)
{
	int temp = 0, vsize = v.size();
	for (int i = 0; i < vsize; i++)
		for (int j = i + 1; j < vsize; j++) {
			temp += food[v[i]][v[j]] + food[v[j]][v[i]];
		}
	return temp;
}
void dfs(int cnt, int idx)
{
	if (cnt == n / 2) {
		for (int i = 0; i < n; i++)
			if (!check[i])
				b.push_back(i);
		ans = min(ans, abs(calc(a) - calc(b)));
		b.clear();
		return;
	}
	//n/2개의 식재료를 사용하여 A음식을 만드는 모든 경우의 수
	for (int i = idx; i < n; i++) {
		if (check[i]) continue;
		a.push_back(i);
		check[i] = true;
		dfs(cnt + 1, i);
		a.pop_back();
		check[i] = false;
	}
}
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> n;
		ans = 2e9;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> food[i][j];
		dfs(0, 0);
		cout << "#" << test_case << " " << ans << "\n";
		memset(check, 0, sizeof(check));
	}
	return 0;
}