#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int num;
	int temp = 1, nmax = 1, dmax = 1;
	cin >> num;

	int ar[1002] = { 0 };
	int dp[1002] = { 0 };
	for (int i = 1; i <= num; i++)
		cin >> ar[i];
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 1; i <= num; i++) {
		int m = 0;
		nmax = ar[1];
		for (int k = 1; k < i; k++) {
			if (ar[i] > ar[k] && dp[k] > m) {
				m = dp[k];
			}
		}
		dp[i] = m + 1;
		temp = m + 1;
		nmax = ar[i];

		for (int j = i; j <= num; j++) {
			if (nmax < ar[j]) {
				temp++;
				nmax = ar[j];
			}
		}
		if (temp > dmax)
			dmax = temp;
	}

	printf("%d\n", dmax);

	return 0;
}