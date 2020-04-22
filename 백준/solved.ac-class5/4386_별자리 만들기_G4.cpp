#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
double dist(pair<double, double>& a, pair<double, double>& b) {
	return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}
struct cmp {
	bool operator()(pair<int, double>& a, pair<int, double>& b) {
		return a.second > b.second;
	}
};
int main()
{
	int n;
	double ans = 0;
	cin >> n;
	vector<pair<double, double>> v(n);
	vector<bool> visited(n, false);
	for (int i = 0; i < n; i++)
		cin >> v[i].first >> v[i].second;
	priority_queue < pair<int, double >, vector<pair<int, double>>, cmp> pq;
	for (int i = 1; i < n; i++)
		pq.push({ i, dist(v[0], v[i]) });

	while (!pq.empty()) {
		pair<int, double> cur = pq.top();
		pq.pop();
		if (visited[cur.first]) continue;
		visited[cur.first] = true;
		ans += cur.second;
		for (int i = 1; i < n; i++)
			if (!visited[i])
				pq.push({ i, dist(v[cur.first], v[i]) });
	}
	cout << fixed;
	cout.precision(2);
	cout << ans;
}