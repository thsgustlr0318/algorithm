#include <iostream>
#include <algorithm>
#define MAX 10
using namespace std;
int board[MAX][MAX], paper_size[5] = { 5, 5, 5, 5, 5 };
int ans = 2e9, paper_cnt;
bool check(int y, int x, int s)
{
	if (paper_size[s] == 0 || y + s >= MAX || x + s >= MAX) return false;
	for (int i = y; i <= y + s; i++)
		for (int j = x; j <= x + s; j++)
			if (board[i][j] == 0) return false;
	return true;
}
void fillPaper(int y, int x, int s)
{
	for (int i = y; i <= y + s; i++)
		for (int j = x; j <= x + s; j++)
			board[i][j] = 0;
	paper_size[s]--;
}
void deletePaper(int y, int x, int s)
{
	for (int i = y; i <= y + s; i++)
		for (int j = x; j <= x + s; j++)
			board[i][j] = 1;
	paper_size[s]++;
}
void dfs(int cnt)
{
	if (cnt == 0) {
		int temp = 0;
		for (int i = 0; i < 5; i++)
			temp += 5 - paper_size[i];
		ans = min(ans, temp);
		return;
	}
	for (int y = 0; y < MAX; y++)
		for (int x = 0; x < MAX; x++)
			if (board[y][x] == 1) {
				for (int s = 5; s >= 1; s--) {
					if (check(y, x, s - 1)) {
						fillPaper(y, x, s - 1);
						dfs(cnt - s * s);
						deletePaper(y, x, s - 1);
					}
				}
				return;
			}
}
int main()
{
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++) {
			cin >> board[i][j];
			if (board[i][j]) paper_cnt++;
		}
	dfs(paper_cnt);
	ans == 2e9 ? cout << "-1" : cout << ans;
}