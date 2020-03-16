#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
using namespace std;
int sm, sc, si;
int loop[4096];
string program, input;
void setLoop()
{
	memset(loop, 0, sc);
	stack<int> st;
	for (int i = 0; i < sc; i++) {
		if (program[i] == '[') {
			st.push(i);
		}
		else if (program[i] == ']') {
			int prev = st.top();
			st.pop();
			loop[prev] = i, loop[i] = prev;
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) {
		int program_idx = 0, input_idx = 0, arr_idx = 0, loop_idx = 0;
		cin >> sm >> sc >> si;
		cin >> program >> input;
		vector<unsigned char> arr(sm, 0);
		bool flag = false;
		setLoop();
		for (int i = 0; i < 50000000; i++) {
			if (program_idx >= sc) {
				flag = true;
				break;
			}
			if (program[program_idx] == '-') {
				arr[arr_idx]--;
			}
			else if (program[program_idx] == '+') {
				arr[arr_idx]++;
			}
			else if (program[program_idx] == '<') {
				arr_idx = arr_idx - 1 < 0 ? sm - 1 : arr_idx - 1;
			}
			else if (program[program_idx] == '>') {
				arr_idx = arr_idx + 1 == sm ? 0 : arr_idx + 1;
			}
			else if (program[program_idx] == '[') {
				if (arr[arr_idx] == 0) program_idx = loop[program_idx];
			}
			else if (program[program_idx] == ']') {
				if (arr[arr_idx] != 0) program_idx = loop[program_idx];
			}
			else if (program[program_idx] == ',') {
				input_idx == si ? arr[arr_idx] = 255 : arr[arr_idx] = input[input_idx++];
			}
			program_idx++;
			loop_idx = max(loop_idx, program_idx);
		}
		if (flag) 
			cout << "Terminates\n";		
		else 
			cout << "Loops " << loop[loop_idx] << " " << loop_idx << "\n";		
	}
}