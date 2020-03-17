#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define MAX 11
using namespace std;
int n, ans = 2e9;
int people[MAX];
vector<int> node[MAX];
bool select_A[MAX], visit[MAX];
//BFS
bool checkConnected(vector<int> v)
{
	memset(visit, false, sizeof(visit));
	queue<int> q;
	int cnt = 1;
	q.push(v[0]);
	visit[v[0]] = true;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < node[cur].size(); i++) {
			int next = node[cur][i];
			//방문한적 있는 경우나 v선거구에 next가 없는 경우, continue
			if (visit[next] || find(v.begin(), v.end(), next) == v.end()) continue;
			q.push(next);
			visit[next] = true;
			cnt++;
		}
	}
	return cnt == v.size() ? true : false;
}
void calc()
{
	vector<int> A, B;
	for (int i = 1; i <= n; i++) {
		if (select_A[i]) A.push_back(i);
		else B.push_back(i);
	}
	//BFS로 A, B선거구가 모두 연결되어 있는지 확인
	if (!checkConnected(A) || !checkConnected(B)) return;
	int total = 0;
	for (int i = 0; i < A.size(); i++) total += people[A[i]];
	for (int i = 0; i < B.size(); i++) total -= people[B[i]];
	ans = min(ans, abs(total));
}
//선거구 2개로 나누기
void dfs(int cnt, int idx)
{
	//A선거구 갯수가 1~(n-1)인 경우
	if (cnt >= 1 && cnt != n) {
		calc();
	}
	for (int i = idx; i <= n; i++) {
		if (select_A[i]) continue;
		select_A[i] = true;
		dfs(cnt + 1, i + 1);
		select_A[i] = false;
	}
}
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> people[i];
	for (int i = 1; i <= n; i++) {
		int num, a;
		cin >> num;
		while (num--) {
			cin >> a;
			node[i].push_back(a);
		}
	}
	dfs(0, 1);
	ans == 2e9 ? cout << "-1\n" : cout << ans;
}