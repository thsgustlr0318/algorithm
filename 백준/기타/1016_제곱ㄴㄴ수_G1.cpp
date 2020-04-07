#include <iostream>
#include <cmath>
using namespace std;
bool check[1000001];
int main()
{
	long long minv, maxv;
	cin >> minv >> maxv;
	long long sqrmax = sqrt(maxv);
	//2 ~ max의 제곱수까지 탐색
	for (long long i = 2; i <= sqrmax; i++) {
		//min부터 탐색할 수 있도록 start 구함
		long long start = minv / (i * i);
		//소수점 올림
		if (i * i * start != minv) start++;
		//i*i로 나누어지는 값들 true
		for (; start * i * i <= maxv; start++)
			check[start * i * i - minv] = true;
	}
	int count = 0;
	for (int i = 0; i < maxv - minv + 1; i++)
		if (!check[i]) count++;
	cout << count;
}