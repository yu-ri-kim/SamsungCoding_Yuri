## # Puyo Puyo(문제 _ [11559](https://www.acmicpc.net/problem/11559))

뿌요뿌요의 룰은 다음과 같다.

> 필드에 여러 가지 색깔의 뿌요를 놓는다. 뿌요는 중력의 영향을 받아 아래에 바닥이나 다른 뿌요가 나올 때까지 아래로 떨어진다.
> 
> 뿌요를 놓고 난 후, 같은 색 뿌요가 4개 이상 상하좌우로 연결되어 있으면 연결된 같은 색 뿌요들이 한꺼번에 없어진다.
> 
> 뿌요들이 없어지고 나서 위에 다른 뿌요들이 있다면, 역시 중력의 영향을 받아 차례대로 아래로 떨어지게 된다.
> 
> 아래로 떨어지고 나서 다시 같은 색의 뿌요들이 4개 이상 모이게 되면 또 터지게 되는데, 터진 후 뿌요들이 내려오고 다시 터짐을 반복할 때마다 1연쇄씩 늘어난다.
> 
> 터질 수 있는 뿌요가 여러 그룹이 있다면 동시에 터져야 하고 여러 그룹이 터지더라도 한번의 연쇄가 추가된다.

남규는 최근 뿌요뿌요 게임에 푹 빠졌다. 이 게임은 1:1로 붙는 대전게임이라 잘 쌓는 것도 중요하지만, 상대방이 터뜨린다면 연쇄가 몇 번이 될지 바로 파악할 수 있는 능력도 필요하다. 하지만 아직 실력이 부족하여 남규는 자기 필드에만 신경 쓰기 바쁘다. 상대방의 필드가 주어졌을 때, 연쇄가 몇 번 연속으로 일어날지 계산하여 남규를 도와주자!

**입력**
12*6의 문자가 주어진다.

이때 .은 빈공간이고 .이 아닌것은 각각의 색깔의 뿌요를 나타낸다.

R은 빨강, G는 초록, B는 파랑, P는 보라, Y는 노랑이다.(모두 대문자로 주어진다.)

입력으로 주어지는 필드는 뿌요들이 전부 아래로 떨어진 뒤의 상태(즉 뿌요 아래에 빈 칸이 있는 경우는 없음) 이다.

**출력**
현재 주어진 상황에서 몇연쇄가 되는지 출력하라. (하나도 터지지 않는다면 0을 출력하면 된다.)

 
## 예제

	......
	......
	......
	......
	......
	......
	......
	......
	.Y....
	.YG...
	RRYG..
	RRYGG.
	answer : 3


## 풀이
시뮬레이션 문제이다. 뿌요의 맵안에서의 위치와 색깔을 저장하기 위해 struct를 생성했다.

뿌요가 터지면 빈공간으로 내려와야 하는데 그 코드는 remove 함수내에 작성했다.

'전체 맵'을 저장하는 어레이와 '뿌요의 저장 배열'을 저장하는 list 배열을 사용했는데, 구조는 다음과 같다.

    list<> datas[0] 은 0번째 행의 뿌요들이다
    datas[0] = r->r->.->.
    datas[1] = r->r->y->y
    datas[2] = y->y->g->.
    datas[3] = g->g->.->.
    datas[4] = g->.->.->.
    datas[5] = .->.->.->.

 터질 수 있는 뿌요가 여러 그룹이 있다면 동시에 터져야 하기 때문에, 탐색하면서 터질 수 있는 뿌요 그룹이 있다면 그룹내 한 뿌요의 index만 queue에 push 해주면서 진행했다.

## 코드
```cpp
struct Data {
	int i,  j; 
	char color;
};

list<Data> datas[6]; // 뿌요의 저장 배열
string map[12]; // 전체 맵

bool visited[12][12]; // 4개 이상 모였는지 판단하기 위한 큐
bool visited_r[12][12]; // 뿌요를 터트리기 위한 큐
bool chkChange[6]; // 맵이 바뀌었는지 판단

int n; // 사용하는 배열 크기

const int dx[] = { 1,0,-1,0 };
const int dy[] = { 0,1,0,-1 };

int bfs(int i, int j) { // 4개이상의 뿌요가 있는가?
	int cnt = 0;
	queue<pair<int, int>> q;
	q.push({ i,j });
	visited[i][j] = true;

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		int curColor = map[cur.first][cur.second];
		q.pop();
		cnt++; // pop 할때마다 cnt

		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.first + dx[dir];
			int ny = cur.second + dy[dir];

			if (nx < 0 || nx >= n || ny < 0 || ny >= 6) continue;

			if (curColor == map[nx][ny]) { // 같은 색깔 뿌요만 판단
				if (!visited[nx][ny]) {
					visited[nx][ny] = true;
					q.push({ nx,ny });
				}
			}
		}
	}
	return cnt;
}

void remove(queue<pair<int, int>> q) { // 맵에서 뿌요 제거
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		int j = cur.second;
		int i = cur.first;
		char c = map[i][j];

		list<Data>::iterator iter;

		for (iter = datas[j].begin(); iter != datas[j].end(); ++iter) {
			if ((*iter).i == i) {
				datas[j].erase(iter); // 뿌요 리스트에서 제거
				chkChange[j] = true; // 맵의 해당 열이 바뀜을 체크
				break;
			}
		}

		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.first + dx[dir];
			int ny = cur.second + dy[dir];

			if (nx < 0 || nx >= n || ny < 0 || ny >= 6) continue;

			if (c == map[nx][ny]) {
				if (!visited_r[nx][ny]) {
					visited_r[nx][ny] = true;
					q.push({ nx,ny });
				}
			}
		}
	}

	// 리스트 값 -> 배열에 복사
	for (int i = 0; i < 6; i++) {
		if (chkChange[i] == true) {
			list<Data>::iterator iter;

			int x = n - 1;

			for (int j = 0; j < n; j++) { // 먼저 다 .으로 표시해주고
				map[j][i] = '.';
			}

			// 맵에 뿌요 다시 뿌리기
			for (iter = datas[i].begin(); iter != datas[i].end(); ++iter) {
				char c = (*iter).color;
				map[x][i] = c; 
				(*iter).i = x;
				(*iter).j = i;
				x--;
			}
		}
	}
}

int main() {
	string tmp;
	for (int i = 0; i < 12; i++) {
		cin >> tmp;
		if (tmp != "......") { // 빈 공간이 아니라면
			map[n] = tmp ; // 맵에 저장
			n++;
		}
	}

	for (int i= n - 1; i >= 0; i--) { // 거꾸로
		for (int j = 0; j < 6; j++) { // 뿌요값 저장 
			Data d;
			d.i = i; d.j = j;
			d.color = map[i][j];
			datas[j].push_back(d);
		}
	}

	int cnt = 0;
	while (true) { // 터트릴 뿌요가 없을 때까지
		queue<pair<int, int>> q;

		// 초기화
		for (int i = 0; i < n; i++) {
			fill(visited[i], visited[i] + 6, false);
			fill(visited_r[i], visited_r[i] + 6, false);
		}
		fill(chkChange, chkChange + 6, false);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				if (map[i][j] != '.') { // 뿌요라면
					if (!visited[i][j]) {
						int cnt = bfs(i, j);
						if (cnt >= 4) { // 4개 이상 연결되어 있다면
							q.push({ i,j }); // 제거할 블록들 추가
							visited_r[i][j] = true;
						}
					}
				}
			}
		}

		if (q.empty()) { // 터트릴 뿌요가 없다면
			cout << cnt;
			break;
		}
		else {
			remove(q); // 뿌요 터트리기
		}
		cnt++;
	}

}
```
