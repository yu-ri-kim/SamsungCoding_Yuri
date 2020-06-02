#include <iostream>
#include <queue>

using namespace std;

int hx[8] = { -2,-2, -1,-1, 1,1, 2,2 };
int hy[8] = { -1,1, -2,2, -2,2, -1,1 };
int mx[4] = { 0,1,0,-1 };
int my[4] = { 1,0,-1,0 };

int arr[201][201];
bool visited[201][201][31]; // x, y, k를 사용한 횟수 k이상 못씀
int main() {
	int k;
	cin >> k;

	int w, h;
	cin >> w >> h; //h가 행

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> arr[i][j];
		}
	}
	// 0,0 에서 n-1,m-1로 가야한다.

	queue <pair<pair<int, int>, pair<int, int>>> q;
	visited[0][0][0] = true;
	q.push({ {0,0},{0,0} });

	while (!q.empty()) {
		pair<int, int > cur = q.front().first;
		int kCnt = q.front().second.first;
		int distance = q.front().second.second;

		if (cur.first == h - 1 && cur.second == w - 1) {
			cout << distance;
			return 0;
		}

		q.pop();
		

		if (kCnt < k) { // 말의 움직임처럼 움직인다
			for (int i = 0; i < 8; i++) {
				int nx = cur.first + hx[i];
				int ny = cur.second + hy[i];

				if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;

				if (arr[nx][ny] == 0 && !visited[nx][ny][kCnt + 1]) {
					visited[nx][ny][kCnt + 1] = true;
					q.push({ {nx,ny},{kCnt + 1, distance + 1} });
				}
			}
		}

		// 그냥 움직인다
		for (int i = 0; i < 4; i++) {
			int nx = cur.first + mx[i];
			int ny = cur.second + my[i];

			if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;

			if (arr[nx][ny] == 0 && !visited[nx][ny][kCnt]) {
				visited[nx][ny][kCnt] = true;
				q.push({ {nx,ny},{kCnt, distance + 1} });
			}
		}
	}

	cout << -1;
}
