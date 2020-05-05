#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
struct pos {
    int y, x, block;
};
//block: 제거 가능한 block의 좌표(맨 상단 좌측이 {0, 0})
int block[5][4][2] = { {{0,0},{1,0},{1,1},{1,2}}, {{0,0},{1,0},{2,0},{2,-1}}, {{0,0},{1,0},{2,0},{2,1}},{{0,0},{1,0},{1,-1},{1,-2}}, {{0,0},{1,0},{1,-1},{1,1}} };
//blockblank: 제거 가능한 block의 비어있는 좌표
int blockblank[5][2][2] = { {{0,1},{0,2}}, {{0,-1},{1,-1}},{{0,1},{1,1}},{{0,-1},{0,-2}},{{0,-1},{0,1}} };
int moveDir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int solution(vector<vector<int>> board) {
    int answer = 0;
    int n = board.size(), maxv = 0;
    vector<vector<bool>> visit(n, vector<bool>(n, false));
    vector<pos> v;
    //제거 가능한 block 찾아서 v에 넣기
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 0 || visit[i][j]) continue;
            int blocknum = board[i][j], cur = -1;
            visit[i][j] = true;
            bool flag = false;
            for (int k = 0; k < 5; k++) {
                for (int l = 0; l < 4; l++) {
                    int ny = i + block[k][l][0], nx = j + block[k][l][1];
                    if (ny < 0 || nx < 0 || ny >= n || nx >= n || blocknum != board[ny][nx]) break;
                    if (l == 3) flag = true;
                }
                //제거 가능한 block이면 v에 {y좌표, x좌표, block모양} 넣음
                if (flag) {
                    v.push_back({ i, j, k });
                    break;
                }
            }
            //block 탐색 했으면 bfs로 중복 탐색 방지
            queue<pair<int, int>> q;
            q.push({ i, j });
            while (!q.empty()) {
                int cy = q.front().first, cx = q.front().second;
                q.pop();
                for (int k = 0; k < 4; k++) {
                    int ny = cy + moveDir[k][0], nx = cx + moveDir[k][1];
                    if (ny < 0 || nx < 0 || ny >= n || nx >= n || visit[ny][nx] || board[ny][nx] != blocknum) continue;
                    visit[ny][nx] = true;
                    q.push({ ny, nx });
                }
            }
        }
    int blockcnt = v.size();
    vector<bool> check(blockcnt, false);
    //제거 가능한 block들 탐색
    for (int j = 0; j < blockcnt; j++) {
        for (int i = 0; i < blockcnt; i++) {
            if (check[i]) continue;
            //{y1, x1}, {y2, x2}: 비어 있는 block 두칸
            int y = v[i].y, x = v[i].x, b = v[i].block;
            int y1 = y + blockblank[b][0][0], x1 = x + blockblank[b][0][1];
            int y2 = y + blockblank[b][1][0], x2 = x + blockblank[b][1][1];
            //두개의 block들 위에 아무 것도 없는지 확인
            bool flag = true;
            for (; y1 >= 0 && flag; y1--)
                if (board[y1][x1] != 0) flag = false;
            for (; y2 >= 0 && flag; y2--)
                if (board[y2][x2] != 0) flag = false;
            //block 위에 뭐가 있으면, continue
            if (!flag) continue;
            check[i] = true;
            answer++;
            //기존 block 제거
            for (int k = 0; k < 4; k++)
                board[y + block[b][k][0]][x + block[b][k][1]] = 0;
        }
    }
    return answer;
}
int main()
{
    vector<vector<int>> board = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 4, 0, 0, 0},{0, 0, 0, 0, 0, 4, 4, 0, 0, 0},{0, 0, 0, 0, 3, 0, 4, 0, 0, 0},{0, 0, 0, 2, 3, 0, 0, 0, 5, 5},{1, 2, 2, 2, 3, 3, 0, 0, 0, 5},{1, 1, 1, 0, 0, 0, 0, 0, 0, 5} };
    cout << solution(board);
}