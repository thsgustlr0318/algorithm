#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int h = board.size(), w = board[0].size();
    stack<int> s;
    for (int i = 0; i < moves.size(); i++) {
        int cur = moves[i] - 1;
        for (int idx = 0; idx < h; idx++) {
            if (board[idx][cur] != 0) {
                if (!s.empty() && s.top() == board[idx][cur]) {
                    answer += 2;
                    s.pop();
                }
                else
                    s.push(board[idx][cur]);
                board[idx][cur] = 0;
                break;
            }
        }
    }
    return answer;
}