#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct wire {
	int a, b;
	bool operator<(const wire& c) {
		return a < c.a;
	}
};
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int n;
	cin >> n;
	vector<wire> v(n);
	vector<int> lis, pos;
	for (int i = 0; i < n; i++)
		cin >> v[i].a >> v[i].b;
	sort(v.begin(), v.end());
	vector<int>::iterator it;
	for (int idx = 0; idx < n; idx++) {
		if (lis.empty() || lis.back() < v[idx].b) {
			lis.push_back(v[idx].b);
			pos.push_back(lis.size());
		}
		else if ((it = lower_bound(lis.begin(), lis.end(), v[idx].b)) != lis.end()) {
			*it = v[idx].b;
			pos.push_back(distance(lis.begin(), it) + 1);
		}
	}
	cout << v.size() - lis.size() << "\n";
	for (int cnt = lis.size(), idx = n - 1; cnt > 0; idx--) {
		if (pos[idx] == cnt) {
			lis[cnt - 1] = idx;
			cnt--;
		}
	}
	for (int i = 0, j = 0; i < n; i++) {
		if (j >= lis.size() || i != lis[j])
			cout << v[i].a << "\n";
		else
			j++;
	}
	return 0;
}