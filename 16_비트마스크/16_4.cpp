#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 12
const int INF = 2e9;
int n, k, m, l;
//i��° �������� ����
int prerequisite[MAXN];
//i��° �б⿡ �����Ǵ� ���� ����
int classes[10];
//[�б�][����]
int cache[10][1 << MAXN];
int bitCount(int n) 
{
	if (n == 0) return 0;
	return n % 2 + bitCount(n / 2);
}
//�̹��б�: semester, ���� ���� ����: taken
int graduate(int semester, int taken)
{
	//k�� �̻� �������
	if (bitCount(taken) >= k) return 0;
	//m�б� ���� ���
	if (semester == m) return INF;
	//�޸������̼�
	int &ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;
	//�̹� �б� ���� �� �ִ� ���� �� ���� ���� ����
	int canTake = (classes[semester] & ~taken);
	//���� ������ �� ���� ���� ���� �ɷ�����
	for (int i = 0; i < n; i++) {
		if ((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
			canTake &= ~(1 << i);
	}
	//canTake�� ��� �κ����� ��ȸ
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		//�� �б⿡ l���� ���� ����
		if (bitCount(take)> l) continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}
	//�̹� �б⿡ �ƹ� �͵� ���� ���� ���
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