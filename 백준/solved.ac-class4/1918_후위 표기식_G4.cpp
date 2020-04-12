#include <iostream>
#include <string>
#include <stack>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
	string str;
	cin >> str;
	stack<char> s;
	for (int idx = 0; idx < str.size(); idx++) {
		if (str[idx] == '*' || str[idx] == '/') {
			if (!s.empty() && (s.top() == '*' || s.top() == '/')) {
				cout << s.top();
				s.pop();
			}
			s.push(str[idx]);
		}
		else if (str[idx] == '+' || str[idx] == '-') {
			while (!s.empty()) {
				if (s.top() == '(') break;
				cout << s.top();
				s.pop();
			}
			s.push(str[idx]);
		}
		else if (str[idx] == '(')
			s.push(str[idx]);
		else if (str[idx] == ')') {
			while (s.top() != '(') {
				cout << s.top();
				s.pop();
			}
			s.pop();
		}
		else 
			cout << str[idx];		
	}
	while (!s.empty()) {
		if (s.top() != '(')
			cout << s.top();
		s.pop();
	}
}