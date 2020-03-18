#include <iostream>
#include <algorithm>
using namespace std;
struct pos {
	int y, x;
};
//피라미드의 (y, x)좌표 찾기
//a<=b 가정
int calc(int a, int b)
{
	pos ap, bp;
	int idx = 1, cnt = 1, ans = 0;
	bool flag = false;
	while (1) {
		if (idx > a && !flag) {
			ap.y = cnt - 1;
			ap.x = a - (idx - cnt);
			flag = true;
		}
		if (idx > b) {
			bp.y = cnt - 1;
			bp.x = b - (idx - cnt);
			ans = bp.y - ap.y;
			if (ap.x > bp.x) ans += ap.x - bp.x;
			else if (ap.x + (bp.y - ap.y) < bp.x) ans += bp.x - ap.x - bp.y + ap.y;
			return ans;
		}
		idx += cnt++;
	}
}
int main()
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case){
		int a, b;
		cin >> a >> b;
		if (a > b) swap(a, b);
		cout << "#" << test_case << " " << calc(a, b) << "\n";
	}
}
