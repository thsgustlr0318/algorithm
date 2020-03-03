#include <iostream>
#include <vector>
using namespace std;
#define INF 1e9
int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, m, w;
		cin >> n >> m >> w;
		vector<pair<int, int>> node[501];
		vector<int> dist(n + 1, INF);
		dist[1] = 0;
		bool cycle = false;

		for (int i = 0; i < m; i++) {
			int s, e, t;
			cin >> s >> e >> t;
			node[s].push_back(make_pair(e, t));
			node[e].push_back(make_pair(s, t));
		}
		for (int i = 0; i < w; i++) {
			int s, e, t;
			cin >> s >> e >> t;
			node[s].push_back(make_pair(e, -t));
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				for (int k = 0; k < node[j].size(); k++) {
					int ne = node[j][k].first, nk = node[j][k].second;
					if (dist[j] != INF && dist[ne] > nk + dist[j]) {
						dist[ne] = nk + dist[j];
						if (i == n)
							cycle = true;
					}
				}
		cycle == true ? cout << "YES\n" : cout << "NO\n";
	}
}