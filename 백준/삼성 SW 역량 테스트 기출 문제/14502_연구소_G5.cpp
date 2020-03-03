#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX 8

int moveDir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
int n, m;
int arr[MAX][MAX];
int temp[MAX][MAX];
int result;

void BFS(void)
{
	int visit[MAX][MAX];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			visit[i][j] = temp[i][j];

	queue<pair<int, int>> q;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (visit[i][j] == 2)
				q.push(make_pair(i, j));

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextY = y + moveDir[i][0];
			int nextX = x + moveDir[i][1];
			if (0 <= nextY && nextY < n && 0 <= nextX && nextX < m)
				if (visit[nextY][nextX] == 0) {
					visit[nextY][nextX] = 2;
					q.push(make_pair(nextY, nextX));
				}
		}
	}
	int cnt = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (visit[i][j] == 0)
				cnt++;
	result = max(result, cnt);
}



void makeWall(int cnt)
{
	if (cnt == 3) {
		BFS();
		return;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (temp[i][j] == 0) {
				temp[i][j] = 1;
				makeWall(cnt + 1);
				temp[i][j] = 0;
			}
}

int main(void)
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> arr[i][j];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (arr[i][j] == 0) {
				for (int k = 0; k < n; k++)
					for (int l = 0; l < m; l++)
						temp[k][l] = arr[k][l];
				temp[i][j] = 1;
				makeWall(1);
				temp[i][j] = 0;
			}
	cout << result << endl;

	return 0;
}