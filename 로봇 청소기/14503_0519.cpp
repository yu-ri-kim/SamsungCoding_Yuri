#include <iostream>
#include <queue>
using namespace std;

int arr[51][51];
bool visited[51][51];

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