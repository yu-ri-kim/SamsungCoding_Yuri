
## 적록색약(문제 _ [10026](https://www.acmicpc.net/problem/10026))

적록색약은 빨간색과 초록색의 차이를 거의 느끼지 못한다. 따라서, 적록색약인 사람이 보는 그림은 아닌 사람이 보는 그림과는 좀 다를 수 있다.

크기가 N×N인 그리드의 각 칸에 R(빨강), G(초록), B(파랑) 중 하나를 색칠한 그림이 있다. 그림은 몇 개의 구역으로 나뉘어져 있는데, 구역은 같은 색으로 이루어져 있다. 또, 같은 색상이 상하좌우로 인접해 있는 경우에 두 글자는 같은 구역에 속한다. (색상의 차이를 거의 느끼지 못하는 경우도 같은 색상이라 한다)

예를 들어, 그림이 아래와 같은 경우에

	RRRBB
	GGBBB
	BBBRR
	BBRRR
	RRRRR

적록색약이 아닌 사람이 봤을 때 구역의 수는 총 4개이다. (빨강 2, 파랑 1, 초록 1) 하지만, 적록색약인 사람은 구역을 3개 볼 수 있다. (빨강-초록 2, 파랑 1)

그림이 입력으로 주어졌을 때, 적록색약인 사람이 봤을 때와 아닌 사람이 봤을 때 구역의 수를 구하는 프로그램을 작성하시오.

**입력**
첫째 줄에 N이 주어진다. (1 ≤ N ≤ 100)

둘째 줄부터 N개 줄에는 그림이 주어진다.

**출력**
적록색약이 아닌 사람이 봤을 때의 구역의 개수와 적록색약인 사람이 봤을 때의 구역의 수를 공백으로 구분해 출력한다..
  

## 예제

	
	5
	RRRBB
	GGBBB
	BBBRR
	BBRRR
	RRRRR
	answer : 4 3

  

## 풀이

적록색약이 아닌 사람이 봤을 때의 구역의 개수를 먼저 cnt 배열에 저장했다.

1. cnt[0] = 빨간색 구역의 수
2. cnt[1] = 초록색 구역의 수
3. cnt[2] = 파란색 구역의 수

그 다음 적록색약인 사람이 봤을 때의 구역의 개수를 찾기 위해 다시 bfs를 돌린다. bfs를 시작하기전에 사용했던 visited 배열은 모두 초기화 해야 한다.


## 코드

```cpp
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
```