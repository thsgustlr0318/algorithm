#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 2147483647;
struct Pair {
	int first, second;
	bool operator < (const Pair& a) const {
		return second > a.second;
	}
};
int main()
{
	int v, e;
	long long ans = 0;
	cin >> v >> e;
	vector<pair<int, int>> tree[10001];
	vector<bool> visit(v + 1, false);
	for (int i = 0; i < e; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		tree[a].push_back({ b, c });
		tree[b].push_back({ a, c });
	}
	priority_queue<Pair> pq;
	//pq에 1번 정점에서의 모든 가능한 간선 값 집어넣음
	visit[1] = true;
	for (int i = 0; i < tree[1].size(); i++)
		pq.push({ tree[1][i].first, tree[1][i].second });
	//프림 알고리즘
	while (!pq.empty()) {
		Pair current = pq.top();
		pq.pop();
		//이미 정점 방문했으면, continue
		if (visit[current.first]) continue;
		visit[current.first] = true;
		ans += current.second;
		//다음 간선 pq에 집어넣음
		for (int i = 0; i < tree[current.first].size(); i++) {
			if (!visit[tree[current.first][i].first])
				pq.push({ tree[current.first][i].first , tree[current.first][i].second });
		}
	}
	cout << ans;
}