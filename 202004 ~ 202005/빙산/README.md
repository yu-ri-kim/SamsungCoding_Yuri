## 빙산(문제 _ 2573)

지구 온난화로 인하여 북극의 빙산이 녹고 있다. 빙산을 그림 1과 같이 2차원 배열에 표시한다고 하자. 빙산의 각 부분별 높이 정보는 배열의 각 칸에 양의 정수로 저장된다. 

빙산 이외의 바다에 해당되는 칸에는 0이 저장된다. 그림 1에서 빈칸은 모두 0으로 채워져 있다고 생각한다.

<p  align="center">

<img  src="./pic1.JPG">

</p>

그림 1. 행의 개수가 5이고 열의 개수가 7인 2차원 배열에 저장된 빙산의 높이 정보

빙산의 높이는 바닷물에 많이 접해있는 부분에서 더 빨리 줄어들기 때문에, **배열에서 빙산의 각 부분에 해당되는 칸에 있는 높이는 일년마다 그 칸에 동서남북 네 방향으로 붙어있는 0이 저장된 칸의 개수만큼 줄어든다.** 

단, 각 칸에 저장된 높이는 0보다 더 줄어들지 않는다. 바닷물은 호수처럼 빙산에 둘러싸여 있을 수도 있다. 

한 덩어리의 빙산이 주어질 때, 이 빙산이 두 덩어리 이상으로 분리되는 최초의 시간(년)을 구하는 프로그램을 작성하시오. 

그림 1의 빙산에 대해서는 2가 답이다. **만일 전부 다 녹을 때까지 두 덩어리 이상으로 분리되지 않으면 프로그램은 0을 출력한다.**


## 입력과 출력

**입력**
첫 줄에는 이차원 배열의 행의 개수와 열의 개수를 나타내는 두 정수 N과 M이 한 개의 빈칸을 사이에 두고 주어진다. N과 M은 3 이상 300 이하이다. 그 다음 N개의 줄에는 각 줄마다 배열의 각 행을 나타내는 M개의 정수가 한 개의 빈 칸을 사이에 두고 주어진다. 
각 칸에 들어가는 값은 0 이상 10 이하이다. 배열에서 빙산이 차지하는 칸의 개수, 즉, 1 이상의 정수가 들어가는 칸의 개수는 10,000 개 이하이다. **배열의 첫 번째 행과 열, 마지막 행과 열에는 항상 0으로 채워진다.**

**출력**
첫 줄에 빙산이 분리되는 최초의 시간(년)을 출력한다. 만일 빙산이 다 녹을 때까지 분리되지 않으면 0을 출력한다.

## 예제

    5 7
    0 0 0 0 0 0 0
    0 2 4 5 3 0 0
    0 3 0 2 5 2 0
    0 7 6 2 4 0 0
    0 0 0 0 0 0 0

    answer : 2

## 풀이

**1.**  **한번에 모든 빙하의 높이를 바꿔주는 방법** 

두개의 queue를 사용한다. 
queue<pair<int, int>> q; // bfs에 사용할 큐
queue <pair<pair<int, int>, int>> storeQ; // 바뀌는 빙하의 높이를 저장할 큐

1년이 지날때마다 한번에 모든 빙하의 높이가 바뀌어야 하기 때문에 bfs를 진행하며 모든 빙하의 새로운 높이를 저장해주고 bfs가 끝날때마다 arr(빙하 높이 저장 배열)을 새롭게 업데이트 한다.

**2. 빙산이 나눠졌는지 판단하는 방법**
	빙산이 1개의 덩어리라면 첫번째 빙하로 bfs를 했을 때 빙산안에 있는 모든 빙하를 방문한다. 만약 bfs를 또 시작하게 된다면 빙산이 2개 이상이라는 뜻이다.

**3. 만일 빙산이 다 녹을 때까지 분리되지 않았는지 판단하는 방법**
	전체 탐색했을 때 빙하가 하나도 없다면 빙산이 다 녹았다는 뜻이다. 이때 빙산이 분리되었는지 먼저 판단하고 빙하가 없는지 판단해야 한다. 

**4. 마지막에 year - 1 을 하는 이유**
	내 코드에서는 빙산이 분리되었는지 판단하는 과정이 다음과 같다.

1. 빙하를 만나면 bfs를 시작한다.
2. bfs가 끝나면 얼음이 녹은걸 arr에 반영한다. -> 이때 빙산이 분리될 수 있다. -> 1년이 지났다고 생각한다.
3. bfs를 시작할 당시 빙산이 하나였다고 가정한다면 빙하는 모두 visit 상태가 되어서 이중포문을 모두 통과한다.
4. 다시 while문 처음으로 가서 bfsStart, notFound,visited를 초기화 한다.
5. 이미 빙산이 2번에서 분리되었지만 분리 되었음을 판단하지 못했으므로 다시 bfs를 시작한다 -> 빙산이 두개라면 처음 나오는 빙산에 포함되는 빙하의 높이가 바뀐다 -> 1년이 지났다고 생각한다
6. 첫번째로 나오는 빙산은 visit 상태이지만, 두번째로 나오는 빙산은 visit 상태가 아니므로 이중포문에서 다시 한번 bfs를 시작하게 된다.

즉 2번에서 이미 빙산은 분리 되었지만 판단을 5번에서 하므로 일년이 더 추가되게 된다. 그렇기 때문에 결과값을 출력할 때 year -1로 한다.


## 코드

```cpp
	bool  visited[301][301] = { false, };

	int  arr[301][301];

	int  dx[4] = { 0, 1, 0, -1 };

	int  dy[4] = { 1,0,-1,0 };

	  

	queue <pair<pair<int, int>, int>> storeQ; 
	// 바뀌는 빙산 높이 저장 (x,y,새로운높이)


	int  main() {

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

				return  0;

			}

		}

		  

		cout << year-1; // 마지막에 bfs를 한번 더 하기 때문에 -1

	}
```
