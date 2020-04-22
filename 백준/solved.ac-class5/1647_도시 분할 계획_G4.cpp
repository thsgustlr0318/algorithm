#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
struct cmp {
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.second > p2.second;
	}
};
int main()
{
	int n, m, ans = 0, maxv = 0;
	cin >> n >> m;
	vector<vector<pair<int, int>>> v(n + 1);
	vector<bool> used(n + 1, false);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		v[a].push_back({ b, c });
		v[b].push_back({ a, c });
	}
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
	used[1] = true;
	for (int i = 0; i < v[1].size(); i++) {
		pq.push({ v[1][i].first, v[1][i].second });
	}
	while (!pq.empty()) {
		pair<int, int> cur = pq.top();
		pq.pop();
		if (used[cur.first]) continue;
		ans += cur.second;
		maxv = max(maxv, cur.second);
		used[cur.first] = true;
		for (int i = 0; i < v[cur.first].size(); i++)
			pq.push({ v[cur.first][i].first, v[cur.first][i].second });
	}
	cout << ans - maxv;
}