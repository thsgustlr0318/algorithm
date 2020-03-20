#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
using namespace std;
int n, k, cnt, ans;
deque<char> v;
vector<string> words;
void init()
{
	v.clear();
	words.clear();
}
int main()
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> n >> k;
		v.resize(n);
		cnt = n / 4;
		for (int i = 0; i < n; i++)
			cin >> v[i];
		//한 변의 숫자 갯수만큼 반복
		//deque로 맨 뒤 숫자를 앞으로 옮김
		for (int i = 0; i < cnt; i++) {
			v.push_front(v.back());
			v.pop_back();
			for (int j = 0; j < n; ) {
				string str;
				for (int k = 0; k < cnt; k++, j++)
					str += v[j];
				words.push_back(str);
			}
		}
		//내림차순 정렬 후 중복 제거
		sort(words.begin(), words.end(), greater<string>());
		words.erase(unique(words.begin(), words.end()));
		//stoi로 16진수 string 10진수 변환
		ans = stoi(words[k - 1], 0, 16);
		cout << "#" << test_case << " " << ans << "\n";
		init();
	}
	return 0;
}