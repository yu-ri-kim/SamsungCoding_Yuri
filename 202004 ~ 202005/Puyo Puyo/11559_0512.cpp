
#include <iostream>
#include <list>
#include <queue>
using namespace std;

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
