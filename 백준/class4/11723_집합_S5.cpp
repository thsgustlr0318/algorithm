#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int m;
	bool arr[21] = { false };
	cin >> m;
	while (m--) {
		string a;
		int b;
		cin >> a;
		if (!a.compare("add")) {
			cin >> b;
			if (!arr[b])
				arr[b] = true;
		}
		else if (!a.compare("check")) {
			cin >> b;
			if (arr[b])
				cout << "1\n";
			else
				cout << "0\n";
		}
		else if (!a.compare("remove")) {
			cin >> b;
			if (arr[b])
				arr[b] = false;
		}
		else if (!a.compare("toggle")) {
			cin >> b;
			if (arr[b])
				arr[b] = false;
			else
				arr[b] = true;
		}
		else if (!a.compare("all")) {
			for (int i = 1; i <= 20; i++)
				arr[i] = true;
		}
		else if (!a.compare("empty")) {
			for (int i = 1; i <= 20; i++)
				arr[i] = false;
		}
	}
}