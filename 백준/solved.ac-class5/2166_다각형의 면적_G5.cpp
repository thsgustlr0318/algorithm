#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
struct pos {
	double y, x;
};
 double ccw(pos& a, pos& b, pos& c)
{
	double  temp = a.x * b.y + b.x * c.y + c.x * a.y;
	temp -= a.x * c.y + c.x * b.y + b.x * a.y;
	return temp;
}

int main()
{
	int n;
	cin >> n;
	double ans = 0;
	vector<pos> v(n);
	for (int i = 0; i < n; i++) 
		cin >> v[i].x >> v[i].y;	
	for (int i = 1; i < n - 1; i++)
		ans += ccw(v[0], v[i], v[i + 1]);
	ans = abs(ans) / 2;
	cout.setf(ios::fixed);
	cout.precision(1);
	cout << ans;
}