#include <iostream>
#include <vector>
#include <queue>
#define INF 2e9
using namespace std;

struct info {
	int des, value;
	info(int a, int b) { des = a, value = b; }
	bool operator<(const info &a) const {
		return this->value > a.value;
	}
};
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int v, e, k;
	cin >> v >> e >> k;
	vector<pair<int, int>> arr[20001];
	priority_queue<info> pq;
	pq.push(info(k, 0));
	for (int i = 0; i < e; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		arr[u].push_back(make_pair(v, w));
	}
	vector<int> d(v + 1, INF);
	d[k] = 0;

	while (!pq.empty()) {
		info cur = pq.top();
		int curd = cur.des, curv = cur.value;
		pq.pop();

		if (d[curd] < curv)
			continue;
		int size = arr[curd].size();
		for (int i = 0; i < size; i++) {
			int next = arr[curd][i].first;
			int nextdistance = curv + arr[curd][i].second;
			if (nextdistance < d[next]) {
				d[next] = nextdistance;
				pq.push(info(next, nextdistance));
			}
		}
	}
	for (int i = 1; i <= v; i++) {
		if (d[i] == INF)
			cout << "INF\n";
		else
			cout << d[i] << "\n";
	}
}