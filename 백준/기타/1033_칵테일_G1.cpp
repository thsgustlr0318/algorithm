#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Info {
	int a, b, p, q;
};
int gcd(int a, int b)
{
	while (b != 0) {
		int c = a % b;
		a = b;
		b = c;
	}
	return a;
}
int lcm(int a, int b)
{
	return (a * b) / gcd(a, b);
}
int main()
{
	int n;
	cin >> n;
	//재료쌍 비율 정보
	vector<Info> v(n - 1);
	//재료의 비율
	vector<int> rate(n, 0);
	//사용됐는지 확인
	vector<bool> visit(n, false);
	for (int i = 0; i < n - 1; i++) {
		cin >> v[i].a >> v[i].b >> v[i].p >> v[i].q;
		if (gcd(v[i].p, v[i].q) != 1) {
			int temp = gcd(v[i].p, v[i].q);
			v[i].p /= temp, v[i].q /= temp;
		}
	}
	//첫번째 재료쌍 비율 설정
	visit[v[0].a] = visit[v[0].b] = true;
	rate[v[0].a] = v[0].p, rate[v[0].b] = v[0].q;
	int cnt = 2;
	//모든 재료를 사용할 때까지 반복
	while (cnt != n) {
		for (int idx = 1; idx < n - 1; idx++) {
			//확인하려는 재료가 둘다 사용되지 않은 경우나, 둘다 사용된 경우 continue
			if (!visit[v[idx].a] && !visit[v[idx].b] || (visit[v[idx].a] && visit[v[idx].b])) continue;
			//비율 확인할 때, 첫번째 재료로 맞춰줌
			if (visit[v[idx].b]) 
				swap(v[idx].a, v[idx].b), swap(v[idx].p, v[idx].q);			
			int rate1 = rate[v[idx].a], rate2 = v[idx].p, afterrate = lcm(rate1, rate2);
			for (int i = 0; i < n; i++)
				if (visit[i])
					rate[i] *= afterrate / rate1;
			visit[v[idx].b] = true;
			rate[v[idx].b] = v[idx].q * (afterrate / rate2);
			cnt++;
		}
	}
	for (int i = 0; i < n; i++)
		cout << rate[i] << " ";
}