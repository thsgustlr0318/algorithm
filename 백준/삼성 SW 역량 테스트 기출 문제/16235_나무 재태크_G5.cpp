#include <iostream>
#include <deque>
using namespace std;
int n, m, k, ans;
int ground[10][10], nutrient[10][10];
int moveDir[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
deque<int> tree[10][10], deadtree[10][10];
int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cin >> nutrient[i][j];
			ground[i][j] = 5;
		}
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		tree[x - 1][y - 1].push_back(z);
	}
	while (k--) {
		//봄
		for (int y = 0; y < n; y++)
			for (int x = 0; x < n; x++) {
				int size = tree[y][x].size();
				for (int i = 0; i < size; i++) {
					int age = tree[y][x].front();
					tree[y][x].pop_front();
					if (ground[y][x] >= age) {
						ground[y][x] -= age;
						tree[y][x].push_back(age + 1);
					}
					else
						deadtree[y][x].push_back(age);
				}
			}
		//여름
		for (int y = 0; y < n; y++)
			for (int x = 0; x < n; x++) {
				while (!deadtree[y][x].empty()) {
					int age = deadtree[y][x].front();
					deadtree[y][x].pop_front();
					ground[y][x] += age / 2;
				}
			}
		//가을
		for (int y = 0; y < n; y++)
			for (int x = 0; x < n; x++) {
				int size = tree[y][x].size();
				for (int i = 0; i < size; i++) {
					if (tree[y][x][i] % 5 != 0) continue;
					for (int j = 0; j < 8; j++) {
						int ny = y + moveDir[j][0], nx = x + moveDir[j][1];
						if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
						tree[ny][nx].push_front(1);
					}
				}
			}
		//겨울
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				ground[i][j] += nutrient[i][j];
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ans += tree[i][j].size();
	cout << ans;
}
//vector구현 -> 시간초과
//sort함수 쓰는 대신 deque사용
//새로생긴 나무는 나이가 1이므로 deque로 앞에 삽입해서 정렬 유지