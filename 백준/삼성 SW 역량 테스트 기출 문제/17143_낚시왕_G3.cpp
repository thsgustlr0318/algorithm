#include <iostream>
using namespace std;
struct pos {
	int speed = 0, direction = 0, size = 0;
};
pos shark[100][100];
int moveDir[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	int row, col, shark_num, ans = 0;
	cin >> row >> col >> shark_num;
	for (int i = 0; i < shark_num; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		d == 1 || d == 2 ? s %= (row - 1) * 2 : s %= (col - 1) * 2;
		shark[r - 1][c - 1] = { s, d - 1, z };
	}
	for (int time = 0; time < col; time++) {
		//상어 잡기
		for (int i = 0; i < row; i++) {
			if (shark[i][time].size != 0) {
				ans += shark[i][time].size;
				shark[i][time] = { 0, 0, 0 };
				break;
			}
		}
		//상어 이동
		pos temp[100][100];
		for(int y=0; y<row; y++)
			for (int x = 0; x < col; x++) {
				if (shark[y][x].size != 0) {
					pos &sh = shark[y][x];
					int ny = y + sh.speed * moveDir[sh.direction][0];
					int nx = x + sh.speed * moveDir[sh.direction][1];
					for (int i = 0; i < 2; i++) {
						if (ny < 0)			ny = -ny, sh.direction = 1;
						else if (nx < 0)		nx = -nx, sh.direction = 2;
						else if (ny >= row)	ny = row - (ny - row + 2), sh.direction = 0;
						else if (nx >= col)	nx = col - (nx - col + 2), sh.direction = 3;
					}
					if (temp[ny][nx].size != 0) {
						if (temp[ny][nx].size < sh.size)
							temp[ny][nx] = sh;
					}
					else
						temp[ny][nx] = sh;
					shark[y][x] = { 0, 0, 0 };
				}
			}
		for (int y = 0; y < row; y++)
			for (int x = 0; x < col; x++)
				shark[y][x] = temp[y][x];
	}
	cout << ans;
}