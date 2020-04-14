#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	int left = 0, right = n - 1, ph = 2e9, x = 0, y = n - 1;
	while (left < right) {
		if (abs(v[left] + v[right]) < ph) {
			ph = abs(v[left] + v[right]);
			x = v[left], y = v[right];
			if (ph == 0)
				break;
		}
		if (v[left] + v[right] < 0)
			left++;
		else
			right--;
	}
	cout << x << " " << y;
}