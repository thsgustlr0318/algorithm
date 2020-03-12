#include <iostream>
#include <algorithm>
#define GOAL 32
using namespace std;
int ans = 0;
int board[33], dice[10], horse[4], score[4];
bool visit[33];
void dfs(int cnt)
{
	if (cnt == 10) {
		ans = max(ans, score[0] + score[1] + score[2] + score[3]);
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (horse[i] != GOAL) {
			int next = horse[i] + dice[cnt];
			//첫번째 코너(10~19)
			if (horse[i] == 5 || (21 <= horse[i] && horse[i] <= 23)) {
				if (horse[i] == 5) next += 15;	//파란칸
				if (24 <= next && next <= 26)	//25~35
					next += 5;
				else if (next == 27)		//40
					next = 20;
				else if (next >= 28)		//도착칸 이상
					next = GOAL;
			}
			//두번째 코너(20~24)
			else if (horse[i] == 10 || (24 <= horse[i] && horse[i] <= 25)) {
				if (horse[i] == 10) next += 13;	//파란칸
				if (26 <= next && next <= 28)	//25~35
					next += 3;
				else if (next == 29)		//40
					next = 20;
				else if (next >= 30)		//도착칸 이상
					next = GOAL;
			}
			//세번째 코너(30~25, 25~35)
			else if (horse[i] == 15 || (26 <= horse[i] && horse[i] <= 31)) {
				if (horse[i] == 15) next += 10;	//파란칸
				if (next == 32)			//40
					next = 20;
				else if (next >= 33)		//도착칸 이상
					next = GOAL;
			}
			//가장자리
			else {
				next = horse[i] + dice[cnt];
				if (next >= 21)			//도착칸 이상
					next = GOAL;
			}
			//마지막칸이 아닌데 말이 있는경우, 다음말 확인
			if (next != GOAL && visit[next]) continue;
			int prev = horse[i];
			visit[prev] = false;
			visit[next] = true;
			horse[i] = next;
			score[i] += board[next];
			dfs(cnt + 1);
			visit[prev] = true;
			visit[next] = false;			
			horse[i] = prev;
			score[i] -= board[next];
		}
	}
}
int main()
{
	//체스판 셋팅
	for (int i = 0, value = 0; i <= 20; i++, value += 2)	board[i] = value;		//가장자리
	for (int i = 21, value = 13; i <= 23; i++, value += 3)	board[i] = value;	//13~19
	for (int i = 24, value = 22; i <= 25; i++, value += 2)	board[i] = value;	//22~24
	for (int i = 26, value = 28; i <= 28; i++, value--)	board[i] = value;		//28~26
	for (int i = 29, value = 25; i <= 31; i++, value += 5)	board[i] = value;	//25~35
	board[GOAL] = 0;
	for (int i = 0; i < 10; i++) 
		cin >> dice[i];
	dfs(0);
	cout << ans;
}