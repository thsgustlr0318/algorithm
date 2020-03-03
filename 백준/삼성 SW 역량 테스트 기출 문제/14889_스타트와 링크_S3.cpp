#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int main()
{
	int n, arr[20][20], mid, result = 2e9;;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];
	vector<int> v;
	mid = n / 2;
	for (int i = 0; i < mid; i++)	v.push_back(0);
	for (int i = 0; i < mid; i++)	v.push_back(1);
	do {
		int start = 0, link = 0;
		vector<int> s, l;
		for (int i = 0; i < n; i++) {
			if (v[i] == 0) s.push_back(i);
			else l.push_back(i);
		}
		for (int i = 0; i < mid; i++)
			for (int j = i + 1; j < mid; j++) {
				start += arr[s[i]][s[j]] + arr[s[j]][s[i]];
				link += arr[l[i]][l[j]] + arr[l[j]][l[i]];
			}
		result = min(result, abs(start - link));
	} while (next_permutation(v.begin(), v.end()));
	cout << result;
}