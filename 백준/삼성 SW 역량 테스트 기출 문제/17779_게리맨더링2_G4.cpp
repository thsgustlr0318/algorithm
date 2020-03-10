#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, ans = 2e9;
int arr[21][21];
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> arr[i][j];
	for (int x = 1; x <= n; x++)
		for (int y = 2; y <= n; y++)
			//d1, d2조건 : (d1, d2 ≥ 1, 1 ≤ x < x+d1+d2 ≤ N, 1 ≤ y-d1 < y < y+d2 ≤ N)
			for (int d1 = 1; d1 <= y - 1 && d1 <= n - x - 1; d1++)
				for (int d2 = 1; d2 <= n - y && d2 <= n - x - d1; d2++) {
					//각 x, y, d1, d2조건에 따라 모든 경우 확인
					vector<int> population(5);
					for (int r = 1; r <= n; r++)
						for (int c = 1; c <= n; c++) {
							//선거구 조건 && !(경계선 넘어갈 조건)
							if (r < x + d1 && c <= y && !(r >= x && c >= y - (r - x))) population[0] += arr[r][c];
							else if (r <= x + d2 && y < c && !(r >= x && c <= y + (r - x))) population[1] += arr[r][c];
							else if (x + d1 <= r && c < y - d1 + d2 && !(r <= x + d1 + d2 && c >= (y - d1 + d2 - (x + d1 + d2 - r)))) population[2] += arr[r][c];
							else if (x + d2 < r && y - d1 + d2 <= c && !(r <= x + d1 + d2 && c <= (y - d1 + d2 + (x + d1 + d2 - r)))) population[3] += arr[r][c];
							else population[4] += arr[r][c];
						}
					sort(population.begin(), population.end());
					int diff = population[4] - population[0];
					ans = min(ans, diff);
				}
	cout << ans;
}
//조건 설정(경계선)