#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
int n, l, p, ans, idx;
int main()
{
	cin >> n;
	vector<pair<int, int>> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i].first >> v[i].second;	
	cin >> l >> p;
	//주유소 거리순으로 정렬
	sort(v.begin(), v.end());
	//pq = 현재 연료량으로 갈 수 있는 주유소에서 채울 수 있는 연료량 오름차순
	priority_queue<int> pq;
	while (p < l) {
		//현재 연료량 안에 갈 수 있는 주유소면 pq에 넣음
		while (idx < n && v[idx].first <= p) {
			pq.push(v[idx].second);
			idx++;
		}
		if (pq.empty()) break;
		p += pq.top();
		ans++;
		pq.pop();
	}
	cout << (p < l ? -1 : ans);
}