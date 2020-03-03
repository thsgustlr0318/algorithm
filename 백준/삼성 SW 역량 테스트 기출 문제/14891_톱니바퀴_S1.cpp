#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
int saw[4][8];
bool visit[4];

void f(int idx, int dir)
{
	visit[idx] = true;
	if (idx > 0 && !visit[idx - 1] && saw[idx][6] != saw[idx - 1][2])
		f(idx - 1, -dir);
	if (idx < 3 && !visit[idx + 1] && saw[idx][2] != saw[idx + 1][6])
		f(idx + 1, -dir);
	if (dir == 1)
		rotate(saw[idx], saw[idx] + 7, saw[idx] + 8);
	else
		rotate(saw[idx], saw[idx] + 1, saw[idx] + 8);
}

int main()
{
	int k, a, b, result = 0;
	string tmp[4];
	for (int i = 0; i < 4; i++)
		cin >> tmp[i];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 8; j++)
			saw[i][j] = tmp[i][j] - '0';
	cin >> k;
	while (k--) {
		cin >> a >> b;
		fill(visit, visit + 4, false);
		f(a - 1, b);
	}
	for (int i = 0; i < 4; i++)
		result += saw[i][0] << i;
	cout << result;
}