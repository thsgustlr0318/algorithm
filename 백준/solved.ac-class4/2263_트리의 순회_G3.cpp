#include <iostream>
using namespace std;
int inorder[100001], postorder[100001], index[100001];
void printPreOrder(int inbegin, int inend, int postbegin, int postend)
{
	if (inbegin > inend || postbegin > postend)		return;
	int root = postorder[postend], length = index[root] - inbegin;
	cout << root << " ";
	printPreOrder(inbegin, index[root] - 1, postbegin, postbegin + length - 1);	//����
	printPreOrder(index[root] + 1, inend, postbegin + length, postend - 1);		//������
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	int n, t;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> inorder[i];
		index[inorder[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		cin >> postorder[i];
	printPreOrder(1, n, 1, n);
}
//inorder�� postorder�� ������ ��(root)�� �������� ����, ���������� ������ Ž��
//postorder���� length�� �̿��� ����, ���������� ����