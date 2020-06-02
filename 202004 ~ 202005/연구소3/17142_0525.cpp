#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int arr[51][51];
int n, m;
vector<pair<int, int>> v;
bool visited[51][51];
int dx[] = { 1,0,-1,0 };
int dy[] = { 0,1,0,-1 };
int finalTime = 98765432;

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) {
				v.push_back({ i,j });
			}
		}
	}

	vector<int> selectV(v.size(), 1);
	for (int i = 0; i < v.size() - m; i++) {
		selectV[i] = 0;
	}

	do {
		memset(visited, false, sizeof(visited));
		queue < pair<pair<int, int>, int>> q; // i,j, 걸린시간

		for (int i = 0; i < selectV.size(); i++) { // 퍼트릴 바이러스
			if (selectV[i]) {
				q.push({ {v[i].first,v[i].second},0 });
				visited[v[i].first][v[i].second] = true;
			}
		}

		int finish = 0;

		while (!q.empty()) {
			pair<int, int> cur = q.front().first;
			int time = q.front().second;
			q.pop();

			if(arr[cur.first][cur.second]==2) {}
			else if (time > finish) finish = time; // 걸린 시간

			for (int dir = 0; dir < 4; dir++) {
				int nx = dx[dir] + cur.first;
				int ny = dy[dir] + cur.second;

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (!visited[nx][ny] && arr[nx][ny] != 1) { // 벽이 아니고 방문하지 않았다면
					visited[nx][ny] = true;
					q.push({ {nx,ny}, time + 1 });
				}
			}
		}

		bool chk = true;
		// 모든 빈칸에 퍼트리지 못했다면
		for (int i = 0; i < n; i++) {
			if (!chk) break;
			for (int j = 0; j < n; j++) {
				if (!visited[i][j] && arr[i][j] == 0) { // 빈칸인데 방문을 못했다면
					chk = false;
					break;
				}
			}
		}

		if (chk) { // 다 퍼트렸다면
			if (finalTime > finish) finalTime = finish; // 최소 시간으로 업데이트
		}

	} while (next_permutation(selectV.begin(), selectV.end()));

	if (finalTime != 98765432) cout << finalTime;
	else cout << -1;
}