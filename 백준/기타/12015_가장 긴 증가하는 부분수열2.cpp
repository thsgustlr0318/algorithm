#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int n;
	cin >> n;
	vector<int> v(n), arr, pos(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	vector<int>::iterator it;
	for (int idx = 0; idx < n; idx++) {
		if (arr.empty() || arr.back() < v[idx]) {
			arr.push_back(v[idx]);
			pos[idx] = arr.size();
		}
		else {
			it = lower_bound(arr.begin(), arr.end(), v[idx]);
			*it = v[idx];
			pos[idx] = distance(arr.begin(), it) + 1;
		}
	}
	cout << arr.size() << "\n";
}