#include <iostream>
#include <queue>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	int n, num;
	cin >> n;
	priority_queue<int> left;
	priority_queue<int, vector<int>, greater<int>> right;
	for (int i = 0; i < n; i++) {
		cin >> num;
		if (left.size() > right.size()) right.push(num);
		else left.push(num);
		if (i > 0 && left.top() > right.top()) {
			int temp = left.top();
			left.pop();
			left.push(right.top());
			right.pop();
			right.push(temp);
		}
		cout << left.top() << "\n";
	}
}
//left: 중간값 기준으로 왼쪽 ex) 1, 2, 4(top)
//right: 중간값 기준으로 오른쪽 ex) 5(top), 6, 7