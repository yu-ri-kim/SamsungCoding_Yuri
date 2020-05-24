/*

적록색약은 빨간색과 초록색의 차이를 느끼지 못한다.
구역은 같은 색으로 이루어져 있다.
색상의 차이를 못느끼는 경우에도 같은 색상이라고 한다(빨 = 초)

적록색약인 사람이 봤을때와 아닌 사람이 봤을 때 구역의 수

*/

#include <iostream>
#include <queue>
using namespace std;

bool visited[101][101];
const int dx[4] = { 0,1,0,-1 };
const int dy[4] = { 1,0,-1,0 };

string arr[101];

int cnt[3]; // r, g ,b
int n;

void BFS(char C, int i,int j) { // 시작 좌표
	int select=0;

	if (C == 'R') {
		select = 0;
	}
	else if (C == 'G') {
		select = 1;
	}
	else {
		select = 2;
	}

	cnt[select]++; // 구역 발견

	queue<pair<int, int>> q;
	visited[i][j] = true;
	q.push({ i,j });

	while (!q.empty()) {
		pair<int, int> cur = { q.front().first,q.front().second };
		q.pop();

		for (int k = 0; k < 4; k++) {
			int nx = cur.first + dx[k];
			int ny = cur.second + dy[k];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (!visited[nx][ny] && arr[nx][ny] == C) {
				visited[nx][ny] = true;
				q.push({ nx,ny });
			}
		}
	}
}
int main() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == 'B' && !visited[i][j]) { // 블루 구역
				BFS('B', i, j);
			}
			if (arr[i][j] == 'R' && !visited[i][j]) { // 빨강 구역
				BFS('R', i, j);
			}
			if (arr[i][j] == 'G' && !visited[i][j]) { // 녹색 구역
				BFS('G', i, j);
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}

	int otherCnt = cnt[2];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((arr[i][j] == 'R' || arr[i][j]=='G') && !visited[i][j]) { // 빨강 + 초록
				otherCnt++;
				queue<pair<int, int>> q;
				visited[i][j] = true;
				q.push({ i,j });

				while (!q.empty()) {
					pair<int, int> cur = { q.front().first,q.front().second };
					q.pop();

					for (int k = 0; k < 4; k++) {
						int nx = cur.first + dx[k];
						int ny = cur.second + dy[k];

						if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
						if (!visited[nx][ny] && (arr[nx][ny] == 'R' || arr[nx][ny] =='G')) {
							visited[nx][ny] = true;
							q.push({ nx,ny });
						}
					}
				}
			}
		}
	}

	cout << cnt[0] + cnt[1] + cnt[2] << " " << otherCnt;
}