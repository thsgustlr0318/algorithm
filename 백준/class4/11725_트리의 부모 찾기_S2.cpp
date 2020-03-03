#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> v[100001];
int parent[100001];
int check[100001];
queue<int> q;

int main()
{
	int n;
	scanf("%d", &n);

	parent[1] = 0;
	check[1] = true;
	q.push(1);

	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		v[a].push_back(b);
		v[b].push_back(a);
	}

	while (!q.empty()) {
		int current = q.front();
		q.pop();

		for (int i = 0; i < v[current].size(); i++) {
			int next = v[current][i];
			if (!check[next]) {
				parent[next] = current;
				check[next] = true;
				q.push(next);
			}
		}
	}

	for (int i = 2; i <= n; i++) {
		printf("%d\n", parent[i]);
	}

	return 0;
}