#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
bool cmp(const pair<int, int>& a, const pair<int, int>& b)
{
	if (a.second == b.second) return a.first < b.first;
	return a.second > b.second;
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int n, k;
	long long ans = 0;
	cin >> n >> k;
	vector<pair<int, int>> v(n);
	multiset<int> bag;
	for (int i = 0; i < n; i++)
		cin >> v[i].first >> v[i].second;
	for (int i = 0; i < k; i++) {
		int num;
		cin >> num;
		bag.insert(num);
	}
	sort(v.begin(), v.end(), cmp);
	for (int i = 0; i < n; i++) {
		//가방이 비어있는경우, 탐색 끝
		if (bag.empty()) break;
		//보석을 담을 수 있는 경우
		if (bag.lower_bound(v[i].first) != bag.end()) {
			ans += v[i].second;
			bag.erase(bag.lower_bound(v[i].first));
		}
	}
	cout << ans;
	return 0;
}
//가방이 담을 수 있는 무게가 중복될 수 있으므로 multiset 사용
//그리디 알고리즘으로 보석 가치가 높은것부터 탐색
//보석을 담을 수 있는 가장 작은 가방 사용
///priority_queue로 구현 가능
//보석(무게), 가방 무게순으로 오름차순 정렬한 다음에 
//모든 가방에 대해서 해당하는 가방의 무게제한을 충족하는 보석 넣어주면
//priority_queue의 top에 해당하는 가방이 가질 수 있는 최대 보석 가치 들어있음
