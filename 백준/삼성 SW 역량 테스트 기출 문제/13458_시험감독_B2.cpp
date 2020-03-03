#include <iostream>
using namespace std;
int arr[1000000];
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, b, c;
	long long ans = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	cin >> b >> c;
	for (int i = 0; i < n; i++) {
		arr[i] -= b;
		ans++;
		if (arr[i] > 0)
			arr[i] % c == 0 ? ans += arr[i] / c : ans += arr[i] / c + 1;
	}
	cout << ans;
}