#include <iostream>
#include <queue>
#include <stdlib.h>
using namespace std;

string zzzzz = "";
int t, n;

int main() {
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);

	cin >> t;

	for (int i = 0; i < t; i++) {
		pair<int, int> arr[103];
		int dist[103][103];
		bool visited[103] = { false, };
		pair<int, int> tmp;

		cin >> n;

		// 거리 값 입력
		for (int j = 0; j < n+2; j++) {
			cin >> tmp.first >> tmp.second;
			arr[j] = tmp;
		}

		// 두 장소간 거리
		for (int k = 0; k < n + 2; k++) { 
			for (int h =0; h < n + 2; h++) { 
				dist[k][h] = abs(arr[k].first - arr[h].first)+abs(arr[k].second - arr[h].second);
			}
		}

		queue <pair<int,int>> q;
		q.push({ 0,1000 }); // 출발지,1000
		visited[0] = true;

		while (!q.empty()) {
			int cur = q.front().first;
			int curDist = q.front().second;
			q.pop();

			for (int test = 0; test < n + 2; test++) {
				if (visited[test]) continue;

				int diff = dist[cur][test]; // cur과 test사이의 거리
				if (curDist - diff >= 0) { // 갈 수 있는 거리라면 
					visited[test] = true;
					int newDist = curDist - diff + 1000;
					if (newDist > 1000) newDist = 1000; // 맥주 리필
					q.push({ test, newDist });
				}
			}
		}
		if (visited[n + 1]) zzzzz = zzzzz + "happy\n";
		else zzzzz += "sad\n";
	}
	cout << zzzzz;
}