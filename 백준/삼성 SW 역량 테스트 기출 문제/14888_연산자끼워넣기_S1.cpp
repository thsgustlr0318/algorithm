#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int n, arr[11], plus, minus, mul, div;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	cin >> plus >> minus >> mul >> div;
	vector<int> v;
	for (int i = 0; i < plus; i++)		v.push_back(1);
	for (int i = 0; i < minus; i++)		v.push_back(2);
	for (int i = 0; i < mul; i++)		v.push_back(3);
	for (int i = 0; i < div; i++)		v.push_back(4);
	sort(v.begin(), v.end());
	int maxv = -2e9, minv = 2e9;
	do {
		int result = arr[0];
		for (int i = 0; i < n - 1; i++) {
			if (v[i] == 1)
				result += arr[i + 1];
			else if (v[i] == 2)
				result -= arr[i + 1];
			else if (v[i] == 3)
				result *= arr[i + 1];
			else
				result /= arr[i + 1];
		}
		maxv = max(maxv, result);
		minv = min(minv, result);
	} while (next_permutation(v.begin(), v.end()));
	cout << maxv << endl << minv;
}