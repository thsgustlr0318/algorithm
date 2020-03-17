#include <iostream>
#include <vector>
#include <string>
#define MAX_SIZE 1000
using namespace std;
char decompressed[MAX_SIZE][MAX_SIZE];
//압축 풀어서 decompressed에 넣어줌
//후에 뒤집어서 다시 압축
void decompress(string::iterator& it, int y, int x, int size)
{
	//한 글자를 검사할 때마다 반복자를 한 칸 앞으로 옮긴다
	char head = *(it++);
	//기저사례: 첫 글자가 b 또는 w인 경우
	if (head == 'b' || head == 'w') {
		for (int dy = 0; dy < size; dy++)
			for (int dx = 0; dx < size; dx++)
				decompressed[y + dy][x + dx] = head;
	}
	else {
		int half = size / 2;
		decompress(it, y, x, half);
		decompress(it, y, x + half, half);
		decompress(it, y + half, x, half);
		decompress(it, y + half, x + half, half);
	}
}
//압축을 풀지 않고 뒤집는 방법
string reverse(string::iterator& it)
{
	char head = *it;
	++it;
	if (head == 'b' || head == 'w')
		return string(1, head);
	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft = reverse(it);
	string lowerRight = reverse(it);
	//각각 위와 아래 조각들의 위치를 바꾼다.
	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}
int main()
{
	int c;
	cin >> c;
	while (c--) {
		string str;
		cin >> str;
		auto it = str.begin();
		cout << reverse(it) << "\n";
	}
}