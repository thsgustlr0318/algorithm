#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INF 1e9
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	int arr[100][100];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			arr[i][j] = INF;
			if (i == j) arr[i][j] = 0;
		}
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		arr[a - 1][b - 1] = min(arr[a - 1][b - 1], c);
	}
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			arr[i][j] == INF ? cout << "0 " : cout << arr[i][j] << " ";
		cout << "\n";
	}
	return 0;
}