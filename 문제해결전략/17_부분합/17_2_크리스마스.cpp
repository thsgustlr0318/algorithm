#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int waysToBuy(const vector<int> &psum, int k) {
	const int MOD = 20091101;
	int ret = 0;
	//psum[]�� �� �� ī��Ʈ
	vector<long long> count(k, 0);
	for (int i = 0; i < psum.size(); i++)
		count[psum[i]]++;
	//ī��Ʈ�� 2�̻��̸� ���� ��� ���� ����
	for (int i = 0; i < k; i++)
		if (count[i] >= 2)
			ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
	return ret;
}

int maxBuys(const vector<int>& psum, int k) {
	//ret : �������� �� �� �ִ� �ִ� Ƚ��
	vector<int> ret(psum.size(), 0);
	//prev[s]=psump[]�� s���� ������ ��ġ
	vector<int> prev(k, -1);
	for (int i = 0; i < psum.size(); i++) {
		//i��° ���ڸ� �ƿ� ������� �ʴ� ���
		if (i > 0)
			ret[i] = ret[i - 1];
		else
			ret[i] = 0;
		//psum[i]�� ������ �� ���� ������, prev[psum[i]]+1���� ������� �� �� ����
		int loc = prev[psum[i]];
		if (loc != -1) ret[i] = max(ret[i], ret[loc] + 1);
		//prev[]�� ���� ��ġ�� ����Ѵ�.
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