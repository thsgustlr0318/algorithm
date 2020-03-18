#include <iostream>
#include <vector>
using namespace std;
int n, m;
vector<int> v;
void dfs(int idx, int cnt)
{
	if (cnt == m) {
		for (auto it = v.begin(); it != v.end(); it++)
			cout << *it << " ";
		cout << "\n";
		return;
	}
	for (int i = idx; i <= n; i++) {
		v.push_back(i);
		dfs(i, cnt + 1);
		v.pop_back();
	}
}
int main()
{
	ios_base::sync_with_stdio(false), cout.tie(NULL);
	cin >> n >> m;
	dfs(1, 0);
}