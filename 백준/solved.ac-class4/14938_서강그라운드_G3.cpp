#include <iostream>
#include <algorithm>
using namespace std;
#define INF 1e9
int item[101], dist[101][101];
int main()
{
	int n, m, r, a, b, l, ans = 0;
	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++) {
		cin >> item[i];
		for (int j = 1; j <= n; j++) {
			dist[i][j] = INF;
			if (i == j) dist[i][j] = 0;
		}
	}
	for (int i = 1; i <= r; i++) {
		cin >> a >> b >> l;
		dist[a][b] = dist[b][a] = l;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	for (int i = 1; i <= n; i++) {
		int temp = 0;
		for (int j = 1; j <= n; j++)
			if (dist[i][j] <= m) temp += item[j];
		ans = max(ans, temp);
	}
	cout << ans;
}
//플로이드-와살
//수색범위(m)보다 낮으면 더함 