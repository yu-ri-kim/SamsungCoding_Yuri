

## 상범 빌딩(문제 _ [6593](https://www.acmicpc.net/problem/6593))

당신은 상범 빌딩에 갇히고 말았다. 여기서 탈출하는 가장 빠른 길은 무엇일까? 상범 빌딩은 각 변의 길이가 1인 정육면체(단위 정육면체)로 이루어져있다. 각 정육면체는 금으로 이루어져 있어 지나갈 수 없거나, 비어있어서 지나갈 수 있게 되어있다. 

**당신은 각 칸에서 인접한 6개의 칸(동,서,남,북,상,하)으로 1분의 시간을 들여 이동할 수 있다.** 즉, 대각선으로 이동하는 것은 불가능하다. 그리고 상범 빌딩의 바깥면도 모두 금으로 막혀있어 출구를 통해서만 탈출할 수 있다.

당신은 상범 빌딩을 탈출할 수 있을까? 만약 그렇다면 얼마나 걸릴까?


## 입력과 출력

**입력**
입력은 여러 개의 테스트 케이스로 이루어지며, 각 테스트 케이스는 세 개의 정수 L, R, C로 시작한다. L(1 ≤ L ≤ 30)은 상범 빌딩의 층 수이다. R(1 ≤ R ≤ 30)과 C(1 ≤ C ≤ 30)는 상범 빌딩의 한 층의 행과 열의 개수를 나타낸다.

그 다음 각 줄이 C개의 문자로 이루어진 R개의 행이 L번 주어진다. 각 문자는 상범 빌딩의 한 칸을 나타낸다. 금으로 막혀있어 지나갈 수 없는 칸은 '#'으로 표현되고, 비어있는 칸은 '.'으로 표현된다. 당신의 시작 지점은 'S'로 표현되고, 탈출할 수 있는 출구는 'E'로 표현된다. 각 층 사이에는 빈 줄이 있으며, 입력의 끝은 L, R, C가 모두 0으로 표현된다. 시작 지점과 출구는 항상 하나만 있다.

**출력**
각 빌딩에 대해 한 줄씩 답을 출력한다. 만약 당신이 탈출할 수 있다면 다음과 같이 출력한다.

	Escaped in x minute(s).
여기서 x는 상범 빌딩을 탈출하는 데에 필요한 최단 시간이다.

만일 탈출이 불가능하다면, 다음과 같이 출력한다.

	Trapped!

## 예제

	3 4 5
	S....
	.###.
	.##..
	###.#

	#####
	#####
	##.##
	##...

	#####
	#####
	#.###
	####E

	1 3 3
	S##
	#E#
	###

	0 0 0

    answer : Escaped in 11 minute(s).
			 Trapped!

## 풀이
삼차원 배열을 사용해서 풀이한다. [z][x][y] 순으로 생각하고 푼다.
나머지 풀이는 이차원 배열을 이용한 bfs와 동일하게 진행된다.

## 코드

```cpp
// z , x,  y
bool visited[31][31][31];
char arr[31][31][31];
int dx[6] = { 1,0,-1,0,0,0 };
int dy[6] = { 0,1,0,-1,0,0 };
int dz[6] = { 0,0,0,0,-1,1 };

using namespace std;

void init(int l,int r, int c) {
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < r; j++) {
			for (int k = 0; k < c; k++) {
				arr[i][j][k] = '0';
				visited[i][j][k] = false;
			}
		}
	}
}

int main() {
	int l, r, c;

	while (1) {
		bool chk = false;

		cin >> l >> r >> c;

		if (!l && !r && !c) break;

		init(l, r, c); // 배열 초기화
		
		// 거리 ,z, x, y
		pair<pair<int,int>, pair<int, int>> start;
		pair<pair<int, int>, pair<int, int>> end;

		// s은 시작, #은 금, .은 비어있는 칸, E는 출구
        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < r; j++)
            {
                for (int k = 0; k < c; k++)
                {
                    cin >> arr[i][j][k];
					if (arr[i][j][k] == 'S') {
						start = { {0,i},{j,k} };
					}
					if (arr[i][j][k] == 'E') {
						end = { {0,i},{j,k} };
					}
                }
            }
        }
		
		// 거리, z , x , y
		queue<pair<pair<int, int>, pair<int, int>>> q;
		q.push(start);
		visited[start.first.second][start.second.first][start.second.second] = true;

		while (!q.empty()) {
			int curZ = q.front().first.second;
			int curX = q.front().second.first;
			int curY = q.front().second.second;
			int dist = q.front().first.first;

			q.pop();
			if (end.first.second == curZ && end.second.first == curX && end.second.second == curY) {
				cout << "Escaped in " << dist << " minute(s)." << "\n";
				chk = true;
				break;
			}

			for (int dir = 0; dir < 6; dir++) {
				int nz = curZ + dz[dir];
				int nx = curX + dx[dir];
				int ny = curY + dy[dir];

				if (nz < 0 || nz >= l || nx < 0 || nx >= r || ny < 0 || ny >= c) continue;

				if ((arr[nz][nx][ny] == 'E' ||arr[nz][nx][ny] == '.') && !visited[nz][nx][ny]) {
					visited[nz][nx][ny] = true;
					q.push({ { dist + 1, nz }, { nx,ny } });
				}
			}
		}

		if (!chk) cout << "Trapped!\n";
	}
}
```