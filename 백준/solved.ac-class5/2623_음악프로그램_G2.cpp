#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> v(n + 1);
	vector<int> dist(n + 1), result(n);
	for (int i = 0; i < m; i++) {
		int num, a, b;
		//a = 첫번째 팀
		cin >> num >> a;
		for (int j = 0; j < num - 1; j++) {
			cin >> b;
			v[a].push_back(b);
			dist[b]++;
			a = b;
		}
	}
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (dist[i] == 0)
			q.push(i);
	for (int i = 0; i < n; i++) {
		if (q.empty()) {
			cout << "0\n";
			return 0;
		}
		int cur = q.front();
		q.pop();
		result[i] = cur;
		for (int j = 0; j < v[cur].size(); j++) {
			int next = v[cur][j];
			if (--dist[next] == 0)
				q.push(next);
		}
	}
	for (int i = 0; i < n; i++)
		cout << result[i] << "\n";
	return 0;
}