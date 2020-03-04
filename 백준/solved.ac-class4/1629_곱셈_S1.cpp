#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

long long a, b, c, result;
long long calc(long long n, long long m)
{
	if (m == 1)
		return n;
	long long half = calc(n, m / 2) % c;
	if (m % 2 == 0)
		return (half * half) % c;
	else
		return ((half*half) % c) * (n%c);
}
int main() {
	cin >> a >> b >> c;
	result = calc(a, b) % c;
	cout << result;
}