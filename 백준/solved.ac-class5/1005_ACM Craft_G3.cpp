#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Pair {
	int building, time;
	bool operator<(const Pair& a) const {
		return time > a.time;
	}
};
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int t, n, k, w;
	cin >> t;
	while (t--) {
		cin >> n >> k;
		int ans = 0;
		//time[idx]= idx건물 짓는데 걸리는 시간, indegree[idx]= idx건물의 선행 갯수
		vector<int> time(n + 1), indegree(n + 1, 0);
		vector<vector<int>> v(n + 1);
		priority_queue<Pair> pq;
		for (int i = 1; i <= n; i++)
			cin >> time[i];
		for (int i = 1; i <= k; i++) {
			int x, y;
			cin >> x >> y;
			v[x].push_back(y);
			indegree[y]++;
		}
		cin >> w;
		for (int i = 1; i <= n; i++)
			if (indegree[i] == 0)
				pq.push({ i, time[i] });
		
		while (1) {
			//q: 짓기 시작할 수 있는 건물
			queue<int> q;
			//flag = w건물을 다 지었는지 확인
			bool flag = false;
			//pq 돌면서 ans시간에 건물이 지어졌으면, 해당하는 건물을 선행 조건으로 가진 건물들 degree 낮춰줌
			while (!pq.empty() && pq.top().time == ans) {
				if (pq.top().building == w)
					flag = true;
				int cur = pq.top().building;
				pq.pop();
				//해당하는 건물을 선행 조건으로 가진 건물들 degree 낮춰줌
				for (int idx = 0; idx < v[cur].size(); idx++) {
					//degree가 0이되어 건물을 지을 수 있게 됐으면, q에 넣음
					if (--indegree[v[cur][idx]] == 0) {
						q.push(v[cur][idx]);
					}
				}
			}
			//w건물 지어졌으면, break
			if (flag) break;
			//건물 짓기 끝나는 시간 pq에 넣음
			while (!q.empty()) {
				pq.push({ q.front(), ans + time[q.front()] });
				q.pop();
			}
			ans = pq.top().time;
		}
		cout << ans << "\n";
	}
}
//위상정렬 사용해서 구현한 코드
/*
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	int t, n, k, w;
	cin >> t;
	while (t--) {
		cin >> n >> k;
		//time[idx]= idx건물 짓는데 걸리는 시간, indegree[idx]= idx건물의 선행 갯수, result[idx] = idx건물 지을 수 있는 시간
		vector<int> time(n + 1), indegree(n + 1, 0), result(n + 1, 0);
		vector<vector<int>> v(n + 1);
		queue<int> q;
		for (int i = 1; i <= n; i++)
			cin >> time[i];
		for (int i = 1; i <= k; i++) {
			int x, y;
			cin >> x >> y;
			v[x].push_back(y);
			indegree[y]++;
		}
		cin >> w;
		for (int i = 1; i <= n; i++)
			if (indegree[i] == 0)
				q.push(i);
		//위상정렬
		//w건물의 선행 건물 모두 확인
		while (indegree[w] > 0) {
			int cur = q.front();
			q.pop();
			for (int i = 0; i < v[cur].size(); i++) {
				result[v[cur][i]] = max(result[v[cur][i]], result[cur] + time[cur]);
				if (--indegree[v[cur][i]] == 0)
					q.push(v[cur][i]);
			}
		}
		cout << result[w] + time[w] << "\n";
	}
}
*/