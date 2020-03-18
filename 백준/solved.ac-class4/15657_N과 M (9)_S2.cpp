#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n, m;
vector<int> v, v2;
bool check[8];
void dfs(int cnt)
{
	if (cnt == m) {
		for (auto it = v2.begin(); it != v2.end(); it++)
			cout << *it << " ";
		cout << "\n";
		return;
	}
	int prev = 0;
	for (int i = 0; i < n; i++) {
		if (!check[i] && prev != v[i]) {
			prev = v[i];
			check[i] = true;
			v2.push_back(v[i]);
			dfs(cnt + 1);
			v2.pop_back();
			check[i] = false;
		}
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
	dfs(0);
}