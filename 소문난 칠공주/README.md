## 소문난 칠공주(문제 _ [1941](https://www.acmicpc.net/problem/1941))


총 25명의 여학생들로 이루어진 여학생반은 5*5의 정사각형 격자 형태로 자리가 배치되었고, 얼마 지나지 않아 이다솜과 임도연이라는 두 학생이 두각을 나타내며 다른 학생들을 휘어잡기 시작했다. 곧 모든 여학생이 ‘이다솜파’와 ‘임도연파’의 두 파로 갈라지게 되었으며, 얼마 지나지 않아 ‘임도연파’가 세력을 확장시키며 ‘이다솜파’를 위협하기 시작했다.

위기의식을 느낀 ‘이다솜파’의 학생들은 과감히 현재의 체제를 포기하고, ‘소문난 칠공주’를 결성하는 것이 유일한 생존 수단임을 깨달았다. ‘소문난 칠공주’는 다음과 같은 규칙을 만족해야 한다.

1.  이름이 이름인 만큼, **7명의 여학생**들로 구성되어야 한다.
2.  강한 결속력을 위해, 7명의 자리는 **서로 가로나 세로로 반드시 인접해 있어야 한다.**
3.  화합과 번영을 위해, 반드시 ‘이다솜파’의 학생들로만 구성될 필요는 없다.
4.  그러나 생존을 위해, ‘이다솜파’가 반드시 우위를 점해야 한다. 따라서 7명의 학생 중 ‘이다솜파’의 학생이 적어도 **4명 이상**은 반드시 포함되어 있어야 한다.

여학생반의 자리 배치도가 주어졌을 때, ‘소문난 칠공주’를 결성할 수 있는 모든 경우의 수를 구하는 프로그램을 작성하시오.

**입력**
'S'(이다‘솜’파의 학생을 나타냄) 또는 'Y'(임도‘연’파의 학생을 나타냄)을 값으로 갖는 5*5 행렬이 공백 없이 첫째 줄부터 다섯 줄에 걸쳐 주어진다.

**출력**
첫째 줄에 ‘소문난 칠공주’를 결성할 수 있는 모든 경우의 수를 출력한다.

 
## 예제

	YYYYY
	SYSYS
	YYYYY
	YSYYS
	YYYYY
	answer : 2


## 풀이
백트래킹 문제이다. 로또나 n과 m 처럼 정해진 데이터중에 조건에 맞는 데이터만을 뽑아내는 문제이다.

이때 순서와 상관없이 1,2,3 == 3,2,1 은 같은 경우이기 때문에 오름차순(i,j)으로 학생을 뽑아야 했다.

1. compare(pair p1, pair p2) :  이차원 배열 인덱스 크기 비교. p2가 크면 true
2. chk() : 뽑은 7명의 학생이 다 붙어있는지 판단 -> bfs로 count가 7이면 true
3. func(int k, int s, int y) : 자리 뽑기
뽑은 자리가 이다솜파이면 s+1, 임도연파이면 y+1해서 다시 재귀로 돌린다.

## 코드
```cpp
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
```
