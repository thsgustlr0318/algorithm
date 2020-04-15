#include <iostream>
#include <string>
using namespace std;
string str[9];
int board[9][9];
bool check(int y, int x, int num)
{
	for (int i = 0; i < 9; i++)
		if (board[y][i] == num)
			return false;
	for (int i = 0; i < 9; i++)
		if (board[i][x] == num)
			return false;
	int yy = y / 3 * 3;
	int xx = x / 3 * 3;
	for (int i = yy; i < yy + 3; i++)
		for (int j = xx; j < xx + 3; j++)
			if (board[i][j] == num)
				return false;
	return true;
}
void dfs(int idx)
{
	if (idx == 81) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
				cout << board[i][j];
			cout << "\n";
		}
		exit(0);
	}
	int y = idx / 9, x = idx % 9;
	if (board[y][x] == 0) {
		for (int i = 1; i <= 9; i++) {
			if (!check(y, x, i)) continue;
			board[y][x] = i;
			dfs(idx + 1);
			board[y][x] = 0;
		}
	}
	else
		dfs(idx + 1);
}
int main()
{
	for (int i = 0; i < 9; i++) {
		cin >> str[i];
		for (int j = 0; j < 9; j++)
			board[i][j] = str[i][j] - '0';
	}
	dfs(0);
}