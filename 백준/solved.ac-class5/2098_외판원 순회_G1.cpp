#include <iostream>
#include <vector>
#include <algorithm>
#define MAXV 1e9
using namespace std;
int arr[16][16], n;
int dp[1 << 16][16];
int tsp(int visit, int cur)
{
	//모두 방문했을 경우, 처음으로 돌아옴
	if (visit == (1 << n) - 1) {
		if (arr[cur][0] == 0)
			return MAXV;
		else
			return arr[cur][0];
	}
	int& ret = dp[visit][cur];
	if (ret != 0)
		return ret;
	ret = MAXV;
	for (int next = 0; next < n; next++) {
		//next를 아직 방문하지 않았으며, next로 가는 경로가 있는 경우
		if ((visit & (1 << next)) == 0 && arr[cur][next] != 0) {
			//최소 비용 갱신
			ret = min(ret, tsp(visit | (1 << next), next) + arr[cur][next]);
		}
	}
	return ret;
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];
	cout << tsp(1, 0);
}