#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long my_abs(long long num) {
	if (num < 0) 
		return -num;
	else 
		return num;
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int n;
	cin >> n;
	vector<long long> v(n);
	vector<long long> liquid(3);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	sort(v.begin(), v.end());
	long long ph = 3e9;
	for (int idx = 0; idx < n - 1; idx++) {
		int left = idx + 1, right = n - 1;
		while (left < right) {
			long long sum = v[left] + v[right] + v[idx];
			if (my_abs(sum) < ph) {
				ph = my_abs(sum);
				liquid[0] = v[left], liquid[1] = v[idx], liquid[2] = v[right];
			}
			if (sum < 0)
				left++;
			else
				right--;
		}
	}
	sort(liquid.begin(), liquid.end());
	cout << liquid[0] << " " << liquid[1] << " " << liquid[2];
}