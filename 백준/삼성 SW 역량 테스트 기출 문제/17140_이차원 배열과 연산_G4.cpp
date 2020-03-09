#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int arr[101][101];
struct info {
	int num = 0, count = 0;
	bool operator < (const info & a) const {
		if (count == a.count) return num < a.num;
		return count < a.count;
	}
};
int r, c, k, ans = 0, row = 3, col = 3, arr_size;
void getNextArr(vector<info> &v, vector<info> &temp)
{
	for (int k = 1; k <= 100; k++)
		if (v[k].count != 0)
			temp.push_back({ k, v[k].count });
	sort(temp.begin(), temp.end());
	arr_size = temp.size();
	if (arr_size * 2 > 100) arr_size = 50;
}
int main()
{

	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			cin >> arr[i][j];
	while (ans <= 100) {
		if (arr[r][c] == k)
			break;
		if (row >= col) {
			for (int i = 1; i <= row; i++) {
				vector<info> v(101), temp;
				for (int j = 1; j <= col; j++)
					v[arr[i][j]].count++;
				getNextArr(v, temp);
				for (int k = arr_size * 2; k <= 100; k++) arr[i][k] = 0;
				for (int k = 0, idx = 1; k < arr_size; k++)
					arr[i][idx++] = temp[k].num, arr[i][idx++] = temp[k].count;
				col = max(col, arr_size * 2);
			}
		}
		else {
			for (int i = 1; i <= col; i++) {
				vector<info> v(101), temp;
				for (int j = 1; j <= row; j++)
					v[arr[j][i]].count++;
				getNextArr(v, temp);
				for (int k = arr_size * 2; k <= 100; k++) arr[k][i] = 0;
				for (int k = 0, idx = 1; k < arr_size; k++)
					arr[idx++][i] = temp[k].num, arr[idx++][i] = temp[k].count;
				row = max(row, arr_size * 2);
			}
		}
		ans++;
	}
	ans > 100 ? cout << "-1" : cout << ans;
}
//v에 각 숫자의 갯수
//getNextArr함수에서 각 숫자의 값과 갯수 삽입하고 정렬