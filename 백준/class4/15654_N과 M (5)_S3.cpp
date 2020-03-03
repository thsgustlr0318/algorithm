#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int n, m;
int arr[8];
bool visit[8];
vector<int> v;
void func(int idx)
{
	if (idx == m) {
		for (int i = 0; i < m; i++) {
			printf("%d ", v[arr[i]]);
		}
		printf("\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		if (!visit[i]) {
			visit[i] = true;
			arr[idx] = i;
			func(idx + 1);
			visit[i] = false;
		}
	}
}
int main()
{
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		int num;
		cin >> num;
		v.push_back(num);
	}
	sort(v.begin(), v.end());
	func(0);
}