#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int n, m, a, b;
	cin >> n;
	vector<vector<int>> v(n + 1);
	vector<int> visit(n + 1, 0), parent(n + 1);
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	//BFS
	queue<int> q;
	q.push(1);
	visit[1] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < v[cur].size(); i++) {
			int next = v[cur][i];
			if (visit[next]) continue;
			q.push(next);
			visit[next] = visit[cur] + 1;
			parent[next] = cur;
		}
	}
	cin >> m;
	while (m--) {
		cin >> a >> b;
		if (visit[a] < visit[b])
			swap(a, b);
		while (visit[a] > visit[b])
			a = parent[a];
		while (a != b) {
			a = parent[a];
			b = parent[b];
		}
		cout << a << "\n";
	}
}