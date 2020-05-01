#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
bool checkSquare(int y, int x, vector<string>& board) {
    if (board[y][x] != ' ' && board[y][x] == board[y][x + 1] && board[y][x] == board[y + 1][x] && board[y][x] == board[y + 1][x + 1])
        return true;
    return false;
}
//블록 빈공간 채우기
void setBoard(int m, int n, vector<string>& board) {
    //모든 세로줄
    for (int x = 0; x < n; x++) {
        queue<char> q;
        //블록 있으면 queue에 넣음
        for (int y = m - 1; y >= 0; y--)
            if (board[y][x] != ' ')
                q.push(board[y][x]);
        //빈칸으로 초기화
        for (int y = 0; y < m; y++)
            board[y][x] = ' ';
        //queue에서 아래서부터 채워줌
        for (int y = m - 1; !q.empty(); y--) {
            board[y][x] = q.front();
            q.pop();
        }
    }
}
int solution(int m, int n, vector<string> board) {
    int answer = 0;
    while (1) {
        queue<pair<int, int>> q;
        //4칸 블록 찾기
        for (int i = 0; i < m - 1; i++)
            for (int j = 0; j < n - 1; j++)
                if (checkSquare(i, j, board))
                    q.push({ i, j });
        //4칸 블록 없으면 탈출
        if (q.empty()) 
            break;
        answer += q.size() * 4;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int duplicate = 0;
        while (!q.empty()) {
            int y = q.front().first, x = q.front().second;
            q.pop();
            for (int i = y; i <= y + 1; i++)
                for (int j = x; j <= x + 1; j++)
                    if (board[i][j] == ' ') duplicate++;
            board[y][x] = board[y][x + 1] = board[y + 1][x] = board[y + 1][x + 1] = ' ';
        }
        //중복 개수 빼주기
        answer -= duplicate;
        //맵 재배치
        setBoard(m, n, board);
    }
    return answer;
}
int main()
{
    int m = 6, n = 6;
    vector<string> board = { "TTTANT", "RRFACC", "RRRFCC", "TRRRAA", "TTMMMF", "TMMTTJ" };
    cout << solution(m, n, board);
}