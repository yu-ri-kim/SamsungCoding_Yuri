#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

const int dx[] = { 1,0,-1,0 };
const int dy[] = { 0,1,0,-1 };

int arr[1001][1001];
bool visited[1001][1001][11];
int n, m, k;

int main() {
	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) { 	// 맵 입력
		for (int j = 0; j < m; j++) {
			scanf("%1d", &arr[i][j]);
		}
	}

	queue<tuple<int,int,int,int>> q; // i, j, k, distance
	q.push(make_tuple( 0,0,k,1 ));
	visited[0][0][k] = true; // (0,0)에 벽 부실 수 있는 횟수 k일때 방문 

	while (!q.empty()) {
		pair<int, int> cur = { get<0>(q.front()),get<1>(q.front()) };
		int curK = get<2>(q.front()); // 현재 남아 있는 횟수
		int curD = get<3>(q.front()); // 현재 방문 횟수
		q.pop();

		if (cur.first == n - 1 && cur.second == m - 1) { // 도착했다면
			cout << curD;
			return 0;
		}

		for (int dir = 0; dir < 4; dir++) {
			int nx = dx[dir] + cur.first;
			int ny = dy[dir] + cur.second;

			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

			if (arr[nx][ny] == 0 && !visited[nx][ny][curK]) { // 벽이 아니라면
				visited[nx][ny][curK] = true;
				q.push({ nx,ny,curK, curD + 1 });
			}

			if (arr[nx][ny] == 1) { // 만약 벽이라면
				if (curK > 0) { // 벽을 더 부실 수 있다면
					if (!visited[nx][ny][curK]) { // 아직 방문하지 않았다면
						visited[nx][ny][curK-1] = true; // 벽 한번 부시고 방문
						q.push({ nx,ny,curK - 1, curD + 1 });
					}
				}
			}
		}

	}
	cout << "-1";
}