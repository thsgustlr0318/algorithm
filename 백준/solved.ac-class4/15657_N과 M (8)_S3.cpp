#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n, m;
vector<int> v, v2;
void dfs(int idx, int cnt)
{
	if (cnt == m) {
		for (auto it = v2.begin(); it != v2.end(); it++)
			cout << *it << " ";
		cout << "\n";
		return;
	}
	for (int i = idx; i < n; i++) {
		v2.push_back(v[i]);
		dfs(i, cnt + 1);
		v2.pop_back();
	}
}
int main()
{
	ios_base::sync_with_stdio(false), cout.tie(NULL);
	cin >> n >> m;
	v.resize(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	sort(v.begin(), v.end());
	dfs(0, 0);
}