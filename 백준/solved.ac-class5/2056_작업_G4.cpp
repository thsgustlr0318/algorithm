#include <iostream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
struct Pair {
	int first, second;
	bool operator<(const Pair& a) const {
		return first > a.first;
	}
};
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	int n, time = 0;
	cin >> n;
	//task_count: 선행 작업 갯수
	//task_time: 작업에 걸리는 시간
	//priority_task[idx]: idx작업을 선행으로 가지는 작업들
	//pq.first: 작업을 마치는 시간, pq.second: 작업 번호
	vector<int> task_count(n + 1, 0), task_time(n + 1);
	queue<int> priority_task[10001];
	priority_queue<Pair> pq;
	for (int i = 1; i <= n; i++) {
		cin >> task_time[i] >> task_count[i];
		if (!task_count[i]) {
			pq.push({ task_time[i], i });
			continue;
		}
		for (int j = 0; j < task_count[i]; j++) {
			int a;
			cin >> a;
			priority_task[a].push(i);
		}
	}
	//
	while (!pq.empty()) {
		//start: 새로 시작할 작업들
		queue<int> start;
		//pq의 맨 위가 time이면, 작업 끝남
		//priority_task에서 끝난 작업들 삭제해가며, 선행 작업이 모두 끝난 경우 start에 넣음
		while (!pq.empty() && pq.top().first == time) {
			int end_task = pq.top().second;
			pq.pop();			
			while (!priority_task[end_task].empty()) {
				task_count[priority_task[end_task].front()]--;
				if(task_count[priority_task[end_task].front()] == 0)
					start.push(priority_task[end_task].front());
				priority_task[end_task].pop();
			}
		}
		//새로 시작할 작업이 있으면, pq에 넣음
		while (!start.empty()) {
			int next = start.front();
			start.pop();
			pq.push({ time + task_time[next], next });			
		}
		time++;
	}
	cout << time - 1;
}