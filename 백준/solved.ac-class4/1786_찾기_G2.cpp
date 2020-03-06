#include <iostream>
#include <string>
#include <vector>
using namespace std;
int table[1000001];
int main()
{
	string t, p;
	vector<int> v;
	getline(cin, t);
	getline(cin, p);
	int psize = p.size(), tsize = t.size();
	for (int index = 1, compare = 0; index < psize; index++) {
		while (compare > 0 && p[index] != p[compare]) {
			compare = table[compare - 1];
		}
		if (p[index] == p[compare])
			table[index] = ++compare;
	}	
	for (int t_index = 0, p_index = 0; t_index < tsize; t_index++) {
		if (t[t_index] == p[p_index]) {
			p_index++;
			if (p_index == psize) {
				v.push_back(t_index - psize + 2);
				p_index = table[p_index - 1];
			}
		}
		else {
			if (t[t_index] == p[table[p_index - 1]])
				p_index = table[p_index - 1] + 1;
			else
				p_index = 0;
		}
	}	
	cout << v.size() << "\n";
	for (auto& element : v)
		cout << element << " ";
}
//KMP
/*
for (int index = 0, compare = 0; index < tsize; index++) {
	while (compare > 0 && t[index] != p[compare]) {
		compare = table[compare - 1];
	}
	if (t[index] == p[compare]) {
		compare++;
		if (compare == psize) {
			v.push_back(index - psize + 2);
			compare = table[compare - 1];
		}
	}
}
*/