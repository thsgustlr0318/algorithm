#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<pair<int, int>> v[100001];
int check[100001];
int dist[100001];
int n;

int bfs(int x)
{
	fill(check, check + n + 1, 0);
	fill(dist, dist + n + 1, 0);

	queue<int> q;
	q.push(x);
	check[x] = true;

	while (!q.empty()) {
		int current = q.front();
		q.pop();

		for (int i = 0; i < v[current].size(); i++) {
			int next = v[current][i].first;
			if (!check[next]) {
				q.push(next);
				check[next] = true;
				dist[next] = dist[current] + v[current][i].second;
			}
		}
	}
	int maxv = dist[1];
	int ref = 1;
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

	for (int i = 1; i <= n; i++) {
		int a, b, num;
		cin >> num;
		while (1) {
			cin >> a;
			if (a != -1) {
				cin >> b;
				v[num].push_back(make_pair(a, b));
			}
			else
				break;
		}
	}

	int v1 = bfs(1);
	int v2 = bfs(v1);

	cout << dist[v2] << endl;

	return 0;
}