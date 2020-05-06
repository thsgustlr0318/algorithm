#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int keysize, locksize;
void rotateKey(vector<vector<int>>& key) {
    vector<vector<int>> temp(keysize, vector<int>(keysize, 0));
    for(int i=0; i<keysize; i++)
        for (int j = 0; j < keysize; j++) {
            temp[i][j] = key[keysize - j - 1][i];
        }
    key = temp;
}
bool checkOpen(vector<vector<int>> board) {
    for (int i = 0; i < locksize; i++)
        for (int j = 0; j < locksize; j++)
            if (!board[i][j]) return false;
    return true;
}
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = true;
    keysize = key.size(), locksize = lock.size();
    for (int cnt = 0; cnt < 4; cnt++) {
        rotateKey(key);
        for (int i = -(keysize - 1); i <= locksize + keysize - 2; i++)
            for (int j = -(keysize - 1); j <= locksize + keysize - 2; j++) {
                vector<vector<int>> board(lock);
                bool flag = true;
                for (int y = 0; flag && y < keysize; y++)
                    for (int x = 0; x < keysize; x++) {
                        if (key[y][x] == 0) continue;
                        if (y + i < 0 || y + i >= locksize || x + j < 0 || x + j >= locksize) continue;
                        if (board[y + i][x + j] == 1) {
                            flag = false;
                            break;
                        }
                        board[y + i][x + j] = 1;
                    }
                if (!flag) continue;
                if (checkOpen(board)) return true;
            }
    }
    return false;
}
int main()
{
    vector<vector<int>> key = { {0, 0, 0},{1, 0, 0},{0, 1, 1} };
    vector<vector<int>> lock = { {1, 1, 1},{1, 1, 0},{1, 0, 1} };
    cout << solution(key, lock);
}