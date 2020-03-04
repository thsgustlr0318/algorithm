#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<int> v, v2;
	for (int i = 1; i <= n; i++)
		v.push_back(i);
	for (int i = 1; i <= m; i++)
		v2.push_back(1);
	for (int i = 1; i <= n - m; i++)
		v2.push_back(0);
	do {
		for (int i = 0; i < n; i++)
			if (v2[i] == 1)
				cout << v[i] << " ";
		cout << endl;
	} while (prev_permutation(v2.begin(), v2.end()));
}