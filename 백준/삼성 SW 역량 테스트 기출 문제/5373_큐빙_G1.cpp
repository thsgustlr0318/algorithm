#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
int cube[6][3][3];
int cubearr[54];
string cubeside = "UDFBLR";
int after_rotate[6][12] = {
	{36, 37, 38,  27, 28, 29,  45,46, 47, 18, 19, 20},
	{24, 25, 26, 51, 52, 53, 33, 34, 35, 42, 43, 44},
	{6, 7, 8, 45, 48, 51, 11, 10, 9, 44, 41, 38},
	{53, 50, 47, 2, 1, 0, 36,39, 42, 15, 16,17},
	{18, 21, 24, 9, 12, 15, 35, 32, 29, 0, 3, 6},
	{8, 5, 2, 27, 30, 33, 17, 14, 11, 26, 23, 20}
};

void rotate(int side, int cnt)
{
	int temparr[54];
	while (cnt--) {
		memcpy(temparr, cubearr, sizeof(cubearr));
		int next_rotate[12];
		for (int i = 0; i < 9; i++)
			next_rotate[i] = after_rotate[side][i + 3];
		for (int i = 9; i < 12; i++)
			next_rotate[i] = after_rotate[side][i - 9];
		for (int i = 0; i < 12; i++)
			cubearr[next_rotate[i]] = temparr[after_rotate[side][i]];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cubearr[cube[side][i][j]] = temparr[cube[side][2 - j][i]];
	}
}
int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		char a, b;
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					cube[i][j][k] = i * 9 + j * 3 + k;
		for (int i = 0; i < 54; i++)
			cubearr[i] = i;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a >> b;
			int cnt;
			b == '+' ? cnt = 1 : cnt = 3;
			rotate(cubeside.find(a), cnt);
		}
		for (int i = 0; i < 9; i++) {
			int num = cubearr[i];
			if (num < 9)	cout << "w";
			else if (num < 18) cout << "y";
			else if (num < 27) cout << "r";
			else if (num < 36) cout << "o";
			else if (num < 45) cout << "g";
			else if (num < 54) cout << "b";
			if (i % 3 == 2)
				cout << endl;
		}
	}
}