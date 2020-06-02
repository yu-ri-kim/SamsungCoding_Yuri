#include <iostream>
#include <queue>
using namespace std;

bool visited[301][301] = { false, };
int arr[301][301];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1,0,-1,0 };

queue <pair<pair<int, int>, int>> storeQ; // 바뀌는 빙산 높이 저장 (x,y,새로운높이)

/*
void print(int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}
*/

int main() {
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	bool chk = false; // 빙산 분리 됐는지 확인하는 변수
	int year = 0; // 소요 시간

	while (!chk) { // 빙산이 분리될때까지
		bool bfsStart = false;
		bool notFound = true;

		// 1년이 지날때마다 visited 초기화
		for (int vi = 0; vi < n; vi++) {
			for (int vj = 0; vj < m; vj++) {
				visited[vi][vj] = false;
			}
		}

		for (int i = 1; i < n-1; i++) { // 맨처음과, 마지막 제외
			if (chk) break; // 빙산 분리 되었으면 stop

			for (int j = 1; j < m-1; j++) {
				if (arr[i][j] > 0 && !visited[i][j]) { 
					notFound = false; // 빙산이 발견됨(true - 발견안됨)

					if(bfsStart == false){ // 아직 한번도 bfs를 시작하지 않았다면
						queue<pair<int, int>> q;
						visited[i][j] = true;
						q.push({ i,j });

						bfsStart = true; // bfs 시작

						while (!q.empty()) {
							pair<int, int> cur = q.front();							
							q.pop();

							int seaCnt = 0;

							for (int dir = 0; dir < 4; dir++) {
								int nx = cur.first + dx[dir];
								int ny = cur.second + dy[dir];

								if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

								if (arr[nx][ny] == 0) { // 바다라면
									seaCnt++;
								}
								if (arr[nx][ny] > 0) { // 빙하라면
									if (!visited[nx][ny]) {
										visited[nx][ny] = true;
										q.push({ nx,ny });
									}
								}
							}

							int newH = arr[cur.first][cur.second] - seaCnt;
							if (newH < 0) newH = 0;

							storeQ.push({ {cur.first,cur.second},newH });
						}

						// bfs 끝나면 얼음 녹은거 반영
						while (!storeQ.empty()) {
							int x = storeQ.front().first.first;
							int y = storeQ.front().first.second;
							int h = storeQ.front().second;

							storeQ.pop();
							arr[x][y] = h; // 새로운 높이 반영
						}
						year++; // 1년 지남

					}
					else { // 이미 한번 bfs를 했다면 - 즉 새로운 빙산
						chk = true; // 빙산이 분리됨
						break;
					}
				}
			}
			
		}

		if (notFound) { // 빙산이 하나도 없다면
			cout << 0;
			return 0;
		}
	}

	cout << year-1; // 마지막에 bfs를 한번 더 하기 때문에 -1
}