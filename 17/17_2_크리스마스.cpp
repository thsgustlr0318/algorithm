#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int waysToBuy(const vector<int> &psum, int k) {
	const int MOD = 20091101;
	int ret = 0;
	//psum[]의 각 값 카운트
	vector<long long> count(k, 0);
	for (int i = 0; i < psum.size(); i++)
		count[psum[i]]++;
	//카운트값 2이상이면 조합 방법 개수 더함
	for (int i = 0; i < k; i++)
		if (count[i] >= 2)
			ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
	return ret;
}

int maxBuys(const vector<int>& psum, int k) {
	//ret : 연속으로 살 수 있는 최대 횟수
	vector<int> ret(psum.size(), 0);
	//prev[s]=psump[]이 s였던 마지막 위치
	vector<int> prev(k, -1);
	for (int i = 0; i < psum.size(); i++) {
		//i번째 상자를 아예 고려하지 않는 경우
		if (i > 0)
			ret[i] = ret[i - 1];
		else
			ret[i] = 0;
		//psum[i]를 전에도 본 적이 있으면, prev[psum[i]]+1부터 여기까지 쭉 사 본다
		int loc = prev[psum[i]];
		if (loc != -1) ret[i] = max(ret[i], ret[loc] + 1);
		//prev[]에 현재 위치를 기록한다.
		prev[psum[i]] = i;
	}
	return ret.back();
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		vector<int> psum(n+1);
		for (int i = 0; i < n; i++)
			cin >> psum[i + 1];
		psum[0] = 0;
		for (int i = 1; i <= n; i++)
			psum[i] = (psum[i] + psum[i - 1]) % k;
		cout << waysToBuy(psum, k) << " " << maxBuys(psum, k) << endl;
	}
}