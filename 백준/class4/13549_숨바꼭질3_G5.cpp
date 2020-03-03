#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define INF 2e9
#define MAX 100001

int main()
{
	int n, k;
	cin >> n >> k;
	if (n > k) {
		cout << n - k;
		return 0;
	}
	vector<int> v(MAX, INF);
	queue<int> q;
	v[n] = 0;
	q.push(n);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (cur == k) break;

		if (cur * 2 <= MAX && v[cur * 2] > v[cur]) {
			v[cur * 2] = v[cur];
			q.push(cur * 2);
		}
		if (cur - 1 >= 0 && v[cur - 1] > v[cur] + 1) {
			v[cur - 1] = v[cur] + 1;
			q.push(cur - 1);
		}
		if (cur + 1 <= MAX && v[cur + 1] > v[cur] + 1) {
			v[cur + 1] = v[cur] + 1;
			q.push(cur + 1);
		}
	}
	cout << v[k];
}