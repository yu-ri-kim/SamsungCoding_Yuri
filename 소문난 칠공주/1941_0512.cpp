#include <iostream>
#include <queue>
using namespace std;

string arr[5]; // 자리 배치도
int cnt; // 경우의 수
bool isused[5][5]; // 지금 사용하고 있는지
pair<int, int > datas[7]; // 선택한 자리
bool visited[5][5]; // 다 이어져 있는지 확인을 위한 visited

int dx[] = { -1,0,0,1 };
int dy[] = { 0,-1,1,0 };

// 오름차순으로 구하기 위한 함수
bool compare(pair<int, int> p1, pair<int, int> p2) {
	if (p1.first < p2.first) return true;
	else {
		if (p1.first == p2.first) {
			if (p1.second > p2.second) return false;
			else return true;
		}
		return false;
	}
}

// 자리가 다 이어져있는지 판단
bool chk() {
	queue<pair<int, int>> q;
	int cntcnt = 0;

	for (int i = 0; i < 5; i++) {
		fill(visited[i], visited[i] + 5, false);
	}

	pair<int, int> tmp = datas[0];
	q.push(tmp);
	visited[tmp.first][tmp.second] = true;

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		cntcnt++;

		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.first + dx[dir];
			int ny = cur.second + dy[dir];

			if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;

			if (isused[nx][ny]) {
				if (!visited[nx][ny]) {
					visited[nx][ny] = true;
					q.push({ nx,ny });
				}
			}
		}
	}
	if (cntcnt == 7) return true; // 다 이어져 있다면 true
	else return false;
}
void func(int k, int sCnt, int yCnt) {
	if (yCnt > 3) return; // 임도연파가 4명이상이면 불가능
	if (k == 7 && sCnt >= 4) { // 조건에 맞다면
		if (chk()==true) { // 다 붙어있는지 체크
			cnt++;
		}
		return;
	}

	for (int i=0;i < 5; i++) {
		for (int j=0;j < 5; j++) {
			if (!isused[i][j]) { // 아직 뽑지 않은 자리이고
				if (k == 0 || compare(datas[k - 1], { i,j })) { // 오름차순이라면
					isused[i][j] = true; // 선택
					if (arr[i][j] == 'S') { // 이다솜파
						datas[k] = { i,j };
						func(k + 1, sCnt + 1, yCnt);
					}
					else {
						datas[k] = { i,j }; // 임도연파
						func(k + 1, sCnt, yCnt + 1);
					}
					isused[i][j] = false; // 선택 취소
				}
			}
		}
	}
}

int main() {
	for (int i = 0; i < 5; i++) {
		cin >> arr[i];
	}
	func(0, 0, 0);
	cout << cnt;
}