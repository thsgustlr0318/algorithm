#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX 10001

vector<pair<int, int>> v[MAX];
int check[MAX];
int dist[MAX];
int n;

int bfs(int x)
{
	queue<int> q;
	check[x] = true;
	q.push(x);

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int i = 0; i < v[cur].size(); i++) {
			int next = v[cur][i].first;
			if (!check[next]) {
				check[next] = true;
				q.push(next);
				dist[next] = dist[cur] + v[cur][i].second;
			}
		}
	}
	int maxv = 0, ref = 1;
	for (int i = 1; i <= n; i++) {
		if (maxv < dist[i]) {
			maxv = dist[i];
			ref = i;
		}
	}
	return ref;
}

int main()
{
	cin >> n;

	for (int i = 1; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		v[a].push_back(make_pair(b, c));
		v[b].push_back(make_pair(a, c));
	}
	int v1 = bfs(1);
	fill(check, check + n + 1, 0);
	fill(dist, dist + n + 1, 0);
	int v2 = bfs(v1);

	cout << dist[v2] << endl;

	return 0;
}