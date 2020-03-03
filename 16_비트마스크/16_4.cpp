#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 12
const int INF = 2e9;
int n, k, m, l;
//i번째 선수과목 집합
int prerequisite[MAXN];
//i번째 학기에 개설되는 과목 집합
int classes[10];
//[학기][과목]
int cache[10][1 << MAXN];
int bitCount(int n) 
{
	if (n == 0) return 0;
	return n % 2 + bitCount(n / 2);
}
//이번학기: semester, 들은 과목 집합: taken
int graduate(int semester, int taken)
{
	//k개 이상 들은경우
	if (bitCount(taken) >= k) return 0;
	//m학기 지난 경우
	if (semester == m) return INF;
	//메모이제이션
	int &ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;
	//이번 학기 들을 수 있는 과목 중 듣지 않은 과목
	int canTake = (classes[semester] & ~taken);
	//선수 과목을 다 듣지 않은 과목 걸러내기
	for (int i = 0; i < n; i++) {
		if ((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
			canTake &= ~(1 << i);
	}
	//canTake의 모든 부분집합 순회
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		//한 학기에 l과목 수강 가능
		if (bitCount(take)> l) continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}
	//이번 학기에 아무 것도 듣지 않을 경우
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}

int main()
{	
	int c;
	cin >> c;
	while (c--) {
		cin >> n >> k >> m >> l;
		memset(prerequisite, 0, sizeof(prerequisite));
		memset(classes, 0, sizeof(classes));
		memset(cache, -1, sizeof(cache));
		for (int i = 0; i < n; i++) {
			int num, pre;
			cin >> num;
			for (int j = 0; j < num; j++) {
				cin >> pre;
				prerequisite[i] |= (1 << pre);
			}
		}
		for (int i = 0; i < m; i++) {
			int num, subject;
			cin >> num;
			for (int j = 0; j < num; j++) {
				cin >> subject;
				classes[i] |= (1 << subject);
			}
		}
		int result = graduate(0, 0);
		result == INF ? cout << "IMPOSSIBLE\n" : cout << result << endl;
	}
}