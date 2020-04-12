#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, ans = 0;
//카드가 특정 플레이어에게 보내지게된 경우, true
bool checkRight(vector<int>& cur)
{
	for (int i = 0; i < n; i++) {
		if (cur[i] != i % 3) 
			return false;		
	}
	return true;
}
//카드를 섞었더니 처음으로 돌아온 경우(원하는대로 줄 수 없는 경우), true
bool checkDuplicate(vector<int>& cur, vector<int>& p)
{
	for (int i = 0; i < n; i++)
		if (cur[i] != p[i])
			return false;
	return true;
}
int main()
{
	cin >> n;
	vector<int> p(n), s(n), cur(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		cur[i] = p[i];
	}
	for (int i = 0; i < n; i++)
		cin >> s[i];
	while (1) {		
		if (checkRight(cur)) break;
		//temp = 카드 섞은 후
		vector<int> temp(n);
		for (int i = 0; i < n; i++)
			temp[s[i]] = cur[i];
		cur = temp;
		if (checkDuplicate(cur, p)) {
			ans = -1;
			break;
		}
		ans++;
	}
	cout << ans;
}