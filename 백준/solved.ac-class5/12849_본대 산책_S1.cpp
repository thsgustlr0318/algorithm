#include <iostream>
#define MOD 1000000007
using namespace std;
long long arr[100000][8];
int main()
{
	int d;
	cin >> d;
	arr[1][1] = arr[1][2] = 1;
	for (int i = 2; i < d; i++) {
		arr[i][0] = (arr[i - 1][1] + arr[i - 1][2]) % MOD;
		arr[i][1] = (arr[i - 1][0] + arr[i - 1][2] + arr[i - 1][3]) % MOD;
		arr[i][2] = (arr[i - 1][0] + arr[i - 1][1] + arr[i - 1][3] + arr[i - 1][4]) % MOD;
		arr[i][3] = (arr[i - 1][1] + arr[i - 1][2] + arr[i - 1][4] + arr[i - 1][5]) % MOD;
		arr[i][4] = (arr[i - 1][2] + arr[i - 1][3] + arr[i - 1][5] + arr[i - 1][7]) % MOD;
		arr[i][5] = (arr[i - 1][3] + arr[i - 1][4] + arr[i - 1][6]) % MOD;
		arr[i][6] = (arr[i - 1][5] + arr[i - 1][7]) % MOD;
		arr[i][7] = (arr[i - 1][4] + arr[i - 1][6]) % MOD;
	}
	cout << (arr[d - 1][1] + arr[d - 1][2]) % MOD << "\n";
}