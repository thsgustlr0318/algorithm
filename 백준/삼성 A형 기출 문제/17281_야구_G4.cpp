#include <iostream>
#include <algorithm>
using namespace std;
int n, ans;
int player[51][10];
int order[10];
bool visit[10];
void playGame()
{
	int score = 0, idx = 1;
	for (int inning = 1; inning <= n; inning++) {
		int base[3] = { 0, 0, 0 }, out_count = 3;
		while (out_count) {
			int turn = player[inning][order[idx]];
			if (turn == 0) {
				out_count--;
			}
			else {
				for (int i = 0; i < turn; i++) {
					if (base[2]) score++;	
					base[2] = base[1];
					base[1] = base[0];
					base[0] = 0;
				}
				if (turn == 4) score++;
				else base[turn - 1] = 1;
			}
			idx++;
			if (idx == 10) idx = 1;
		}
	}
	ans = max(ans, score);
}
void dfs(int cnt)
{
	if (cnt > 9) {
		playGame();
		return;
	}
	for (int i = 1; i <= 9; i++) {
		if (visit[i]) continue;
		order[i] = cnt;
		visit[i] = true;
		dfs(cnt + 1);
		visit[i] = false;
	}
}
int main()
{	
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 9; j++) 
			cin >> player[i][j];
	visit[4] = true;
	order[4] = 1;
	dfs(2);
	cout << ans;
}