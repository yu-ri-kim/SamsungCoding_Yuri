
## 벽 부수고 이동하기 2(문제 _ [14442](https://www.acmicpc.net/problem/14442))

N×M의 행렬로 표현되는 맵이 있다. 맵에서 0은 이동할 수 있는 곳을 나타내고, 1은 이동할 수 없는 벽이 있는 곳을 나타낸다. 당신은 (1, 1)에서 (N, M)의 위치까지 이동하려 하는데, 이때 최단 경로로 이동하려 한다. 최단경로는 맵에서 가장 적은 개수의 칸을 지나는 경로를 말하는데, 이때 시작하는 칸과 끝나는 칸도 포함해서 센다.

만약에 이동하는 도중에 벽을 부수고 이동하는 것이 좀 더 경로가 짧아진다면, **벽을 K개 까지 부수고 이동하여도 된다.**

맵이 주어졌을 때, 최단 경로를 구해 내는 프로그램을 작성하시오.

**입력**
첫째 줄에 N(1 ≤ N ≤ 1,000), M(1 ≤ M ≤ 1,000), K(1 ≤ K ≤ 10)이 주어진다. 다음 N개의 줄에 M개의 숫자로 맵이 주어진다. (1, 1)과 (N, M)은 항상 0이라고 가정하자.

**출력**
첫째 줄에 최단 거리를 출력한다. 불가능할 때는 -1을 출력한다.

## 예제

	6 4 1
	0100
	1110
	1000
	0000
	0111
	0000
	
	[answer] 15

  

## 풀이
벽인 부분을 k번까지 부수고 이동해도 되기 때문에 visited 배열을 삼차원으로 설정했다

	visited[i][j][k] # (i,j)에 부실 수 있는 횟수 k번으로 방문한 경우

나머지는 일반적인 bfs 과정과 동일하다

1. 시작점을 queue에 넣고 방문표시를 한다
2. queue가 empty가 아닐때까지 다음과 같은 행동을 반복한다
	- queue의 front 값을 읽어오고 pop 한다

	> 		q.push(make_tuple( 0,0,k,1 )); 			
	> 		visited[0][0][k] = true; // (0,0)에 벽 부실 수 있는 횟수 k일때 방문

	- 현재 위치에서 동서남북으로 탐색한다(dx[], dy[] 이용)
	>		for (int dir = 0; dir < 4; dir++) { }

	- 벽이 아니라면 그냥 지나갈 수 있으므로 큐에 다시 넣는다
	- 벽이고 아직 k가 0이 아니라면 한번 벽을 부시고 진행한다

> 		if (arr[nx][ny] == 0 && !visited[nx][ny][curK]) { // 벽이 아니라면
> 				visited[nx][ny][curK] = true;
> 				q.push({ nx,ny,curK, curD + 1 }); 			
> 		}
> 
> 			if (arr[nx][ny] == 1) { // 만약 벽이라면
> 				if (curK > 0) { // 벽을 더 부실 수 있다면
> 					if (!visited[nx][ny][curK]) { // 아직 방문하지 않았다면
> 						visited[nx][ny][curK-1] = true; // 벽 한번 부시고 방문
> 						q.push({ nx,ny,curK - 1, curD + 1 });
> 					}
> 		} 			


## 코드

```cpp
const int dx[] = { 1,0,-1,0 };
const int dy[] = { 0,1,0,-1 };

int arr[1001][1001];
bool visited[1001][1001][11];
int n, m, k;

int main() {
	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) { 	// 맵 입력
		for (int j = 0; j < m; j++) {
			scanf("%1d", &arr[i][j]);
		}
	}

	queue<tuple<int,int,int,int>> q; // i, j, k, distance
	q.push(make_tuple( 0,0,k,1 ));
	visited[0][0][k] = true; // (0,0)에 벽 부실 수 있는 횟수 k일때 방문 

	while (!q.empty()) {
		pair<int, int> cur = { get<0>(q.front()),get<1>(q.front()) };
		int curK = get<2>(q.front()); // 현재 남아 있는 횟수
		int curD = get<3>(q.front()); // 현재 방문 횟수
		q.pop();

		if (cur.first == n - 1 && cur.second == m - 1) { // 도착했다면
			cout << curD;
			return 0;
		}

		for (int dir = 0; dir < 4; dir++) {
			int nx = dx[dir] + cur.first;
			int ny = dy[dir] + cur.second;

			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

			if (arr[nx][ny] == 0 && !visited[nx][ny][curK]) { // 벽이 아니라면
				visited[nx][ny][curK] = true;
				q.push({ nx,ny,curK, curD + 1 });
			}

			if (arr[nx][ny] == 1) { // 만약 벽이라면
				if (curK > 0) { // 벽을 더 부실 수 있다면
					if (!visited[nx][ny][curK]) { // 아직 방문하지 않았다면
						visited[nx][ny][curK-1] = true; // 벽 한번 부시고 방문
						q.push({ nx,ny,curK - 1, curD + 1 });
					}
				}
			}
		}

	}
	cout << "-1";
}
```