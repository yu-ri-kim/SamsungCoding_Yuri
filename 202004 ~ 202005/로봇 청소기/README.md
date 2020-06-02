## 로봇 청소기(문제 _ [14503](https://www.acmicpc.net/problem/14503))

로봇 청소기가 주어졌을 때, 청소하는 영역의 개수를 구하는 프로그램을 작성하시오.

로봇 청소기가 있는 장소는 N×M 크기의 직사각형으로 나타낼 수 있으며, 1×1크기의 정사각형 칸으로 나누어져 있다. 각각의 칸은 벽 또는 빈 칸이다. 청소기는 바라보는 방향이 있으며, 이 방향은 동, 서, 남, 북중 하나이다. 지도의 각 칸은 (r, c)로 나타낼 수 있고, r은 북쪽으로부터 떨어진 칸의 개수, c는 서쪽으로 부터 떨어진 칸의 개수이다.

로봇 청소기는 다음과 같이 작동한다.

1.  현재 위치를 청소한다.
2.  현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
    1.  왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
    2.  왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
    3.  네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
    4.  네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.

로봇 청소기는 이미 청소되어있는 칸을 또 청소하지 않으며, 벽을 통과할 수 없다.

**입력**
첫째 줄에 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 50)

둘째 줄에 로봇 청소기가 있는 칸의 좌표 (r, c)와 바라보는 방향 d가 주어진다. d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을, 3인 경우에는 서쪽을 바라보고 있는 것이다.

셋째 줄부터 N개의 줄에 장소의 상태가 북쪽부터 남쪽 순서대로, 각 줄은 서쪽부터 동쪽 순서대로 주어진다. 빈 칸은 0, 벽은 1로 주어진다. 지도의 첫 행, 마지막 행, 첫 열, 마지막 열에 있는 모든 칸은 벽이다.

로봇 청소기가 있는 칸의 상태는 항상 빈 칸이다.

**출력**
로봇 청소기가 청소하는 칸의 개수를 출력한다.
  

## 예제

	3 3
	1 1 0
	1 1 1
	1 0 1
	1 1 1
	answer : 1

  

## 풀이

시뮬레이션 문제이다.
로봇 청소기의 작동 방법을 순서대로 구현했다.

	//왼쪽 방향
	const int ndx[] = { 0,-1,0,1 };
	const int ndy[] = { -1,0,1,0 };

	//후진 방향
	const int bdx[] = { 1,0,-1,0 };
	const int bdy[] = { 0,-1,0,1 };

왼쪽으로 회전과 후진하는 것은 배열을 만들어 구현했다.
그리고 현재 로봇청소기의 위치와 방향을 저장할 class를 선언해서 사용했다.

visited 배열을 이용해 해당 위치를 로봇청소기가 청소했음을 식별했다.
그리고 bfs를 이용해 로봇청소기를 돌려주었다.

4 방향 모두 청소할 수 있는 공간이 없다면 후진하거나 작동을 그만두는데 그건 4 방향을 하나하나 queue에 넣는 게 아니라 처음부터 판단하는 식으로 구현했다.

로봇청소기가 왼쪽으로 회전했을 때의 좌표와 후진했을 때의 좌표만 잘 저장한다면 그리 어렵지 않게 해결 할 수 있는 문제이다.

## 코드
```cpp
//북 동 남 서
const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

//왼쪽 방향
const int ndx[] = { 0,-1,0,1 };
const int ndy[] = { -1,0,1,0 };

//후진 방향
const int bdx[] = { 1,0,-1,0 };
const int bdy[] = { 0,-1,0,1 };

class robot {
public:
	int x, y, d;
	robot(int x, int y, int d) {
		this->x = x;
		this->y = y;
		this->d = d;
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	// 로봇청소기의 칸의 좌표 , 바라보는 방향
	int r, c, dd;
	cin >> r >> c >> dd;
	robot rb(r, c, dd);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	queue<robot> q;
	visited[r][c] = true;
	q.push(rb);

	bool chk = true;
	while (!q.empty()) {
		if (!chk) break;
		robot cur = q.front();
		q.pop();

		int cnt = 4;
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];

			if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
				cnt--;
				continue;
			}

			if (visited[nx][ny] || arr[nx][ny] == 1) cnt--;
		}
		if (cnt == 0) { // 4방향 모두 접근 불가능
			cur.x = cur.x + bdx[cur.d];
			cur.y = cur.y + bdy[cur.d];
			if (arr[cur.x][cur.y] == 1) { // 후진 불가능
				chk = false;
				break;
			}
			q.push(cur);
			continue;
		}

		int nx = cur.x + ndx[cur.d];
		int ny = cur.y + ndy[cur.d];

		if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		
		// 청소가 되어 있지 않고 벽이 아닐경우
		if (!visited[nx][ny] && arr[nx][ny] != 1) { // 아직 청소가 되어 있지 않다면
			// 그 방향으로 회전
			if (cur.d == 0) cur.d = 3;
			else if (cur.d == 1) cur.d = 0;
			else if (cur.d == 2) cur.d = 1;
			else cur.d = 2;

			// 전진 후 청소
			visited[nx][ny] = true;
			cur.x = nx;
			cur.y = ny;
			q.push(cur);
		}
		else { // 청소할 공간이 없다면
			if (cur.d == 0) cur.d = 3;
			else if (cur.d == 1) cur.d = 0;
			else if (cur.d == 2) cur.d = 1;
			else cur.d = 2;
			q.push(cur);
		}
	}

	// 로봇청소기가 청소한 구역 수
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j]) cnt++;
		}
	}
	cout << cnt;
}
```