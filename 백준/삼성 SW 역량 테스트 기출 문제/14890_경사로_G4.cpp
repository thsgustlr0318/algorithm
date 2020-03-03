#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

int main()
{
	int n, l, arr[100][100], ans = 0;
	cin >> n >> l;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];
	bool used[100][100];
	fill(&used[0][0], &used[99][99], false);
	for (int i = 0; i < n; i++) {
		int flag = true;
		for (int j = 0; j < n - 1 && flag; j++) {
			if (abs(arr[i][j] - arr[i][j + 1]) >= 2) {
				flag = false;
			}
			else if (arr[i][j] - arr[i][j + 1] == -1) {
				if (j - l + 1 < 0)
					flag = false;
				for (int k = 1; k <= l; k++) {
					if (arr[i][j] != arr[i][j - k + 1])
						flag = false;
					if (used[i][j - k + 1] == true)
						flag = false;
				}
				if (flag) {
					for (int k = 1; k <= l; k++)
						used[i][j - k + 1] = true;
				}
			}
			else if (arr[i][j] - arr[i][j + 1] == 1) {
				if (j + l >= n)
					flag = false;
				for (int k = 1; k <= l; k++) {
					if (arr[i][j + 1] != arr[i][j + k])
						flag = false;
					if (used[i][j + k] == true)
						flag = false;
				}
				if (flag) {
					for (int k = 1; k <= l; k++) {
						used[i][j + k] = true;
					}
				}
			}
		}
		if (flag)
			ans++;
	}
	fill(&used[0][0], &used[99][99], false);
	for (int i = 0; i < n; i++) {
		int flag = true;
		for (int j = 0; j < n - 1 && flag; j++) {
			if (abs(arr[j][i] - arr[j + 1][i]) >= 2) {
				flag = false;
			}
			else if (arr[j][i] - arr[j + 1][i] == -1) {
				if (j - l + 1 < 0)
					flag = false;
				for (int k = 1; k <= l; k++) {
					if (arr[j][i] != arr[j - k + 1][i])
						flag = false;
					if (used[j - k + 1][i] == true)
						flag = false;
				}
				if (flag) {
					for (int k = 1; k <= l; k++)
						used[j - k + 1][i] = true;
				}
			}
			else if (arr[j][i] - arr[j + 1][i] == 1) {
				if (j + l >= n)
					flag = false;
				for (int k = 1; k <= l; k++) {
					if (arr[j + 1][i] != arr[j + k][i])
						flag = false;
					if (used[j + k][i] == true)
						flag = false;
				}
				if (flag) {
					for (int k = 1; k <= l; k++) {
						used[j + k][i] = true;
					}
				}
			}
		}
		if (flag)
			ans++;
	}
	cout << ans;
}