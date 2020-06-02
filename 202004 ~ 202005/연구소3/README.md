
## 연구소3(문제 _ [17142](https://www.acmicpc.net/problem/17142))
인체에 치명적인 바이러스를 연구하던 연구소에 승원이가 침입했고, 바이러스를 유출하려고 한다. 바이러스는 활성 상태와 비활성 상태가 있다. 가장 처음에 모든 바이러스는 비활성 상태이고, 활성 상태인 바이러스는 상하좌우로 인접한 모든 빈 칸으로 동시에 복제되며, 1초가 걸린다. 승원이는 연구소의 바이러스 M개를 활성 상태로 변경하려고 한다.

연구소는 크기가 N×N인 정사각형으로 나타낼 수 있으며, 정사각형은 1×1 크기의 정사각형으로 나누어져 있다. 연구소는 빈 칸, 벽, 바이러스로 이루어져 있으며, 벽은 칸 하나를 가득 차지한다. **활성 바이러스가 비활성 바이러스가 있는 칸으로 가면 비활성 바이러스가 활성으로 변한다.**

예를 들어, 아래와 같이 연구소가 생긴 경우를 살펴보자. 0은 빈 칸, 1은 벽, 2는 바이러스의 위치이다.

	2 0 0 0 1 1 0
	0 0 1 0 1 2 0
	0 1 1 0 1 0 0
	0 1 0 0 0 0 0
	0 0 0 2 0 1 1
	0 1 0 0 0 0 0
	2 1 0 0 0 0 2

시간이 최소가 되는 방법은 아래와 같고, 4초만에 모든 칸에 바이러스를 퍼뜨릴 수 있다.

	0 1 2 3 - - 2
	1 2 - 3 - 0 1
	2 - - 2 - 1 2
	3 - 2 1 2 2 3
	3 2 1 0 1 - -
	4 - 2 1 2 3 4
	* - 3 2 3 4 *

연구소의 상태가 주어졌을 때, 모든 빈 칸에 바이러스를 퍼뜨리는 최소 시간을 구해보자.

**입력**
첫째 줄에 연구소의 크기 N(4 ≤ N ≤ 50), 놓을 수 있는 바이러스의 개수 M(1 ≤ M ≤ 10)이 주어진다.

둘째 줄부터 N개의 줄에 연구소의 상태가 주어진다. 0은 빈 칸, 1은 벽, 2는 바이러스를 놓을 수 있는 위치이다. 2의 개수는 M보다 크거나 같고, 10보다 작거나 같은 자연수이다.

**출력**
연구소의 모든 빈 칸에 바이러스가 있게 되는 최소 시간을 출력한다. 바이러스를 어떻게 놓아도 **모든 빈 칸에 바이러스를 퍼뜨릴 수 없는 경우에는 -1을 출력한다.**

## 예제

	7 3
	2 0 0 0 1 1 0
	0 0 1 0 1 2 0
	0 1 1 0 1 0 0
	0 1 0 0 0 0 0
	0 0 0 2 0 1 1
	0 1 0 0 0 0 0
	2 1 0 0 0 0 2
	answer : 4

  

## 풀이
연구소2와 매우 유사한 문제이다. 

2 - 바이러스를 놓을 수 있는 장소
입력 받을때 2라면 바이러스를 놓을 수 있는 장소이기 때문에 따로 벡터에 저장한다. 저장해 놓은 값을 이용해 어떤 바이러스를 활성화 시킬 건지 정한다(조합)

조합은 c++에 내장되어 있는 next_permutation() 함수를 이용해 구현했다. 
모든 경우의 수를 확인할 때마다 *visited[] 배열을 초기화 해주어야 한다.*

그리고 시간초과를 막기 위해 바이러스를 활성화 시키면서 queue에 push하고 visited를 true로 바꾼다.

나머지는 bfs()를 이용해서 바이러스를 퍼트려주고, 바이러스를 다 못 퍼트리는 경우만 확인해주면 된다.

걸린 시간을 구할 때 바이러스가 활성화 되는 시간은 추가하지 않는다

> (if(arr[cur.first][cur.second]==2) {}

바이러스를 다 퍼트렸다면 이중 포문을 이용해 빈칸이지만 방문하지 않은 곳이 있는지 판단한다. 

## 코드

```cpp
int arr[51][51];
int n, m;
vector<pair<int, int>> v;
bool visited[51][51];
int dx[] = { 1,0,-1,0 };
int dy[] = { 0,1,0,-1 };
int finalTime = 98765432;

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) {
				v.push_back({ i,j });
			}
		}
	}

	vector<int> selectV(v.size(), 1);
	for (int i = 0; i < v.size() - m; i++) {
		selectV[i] = 0;
	}

	do {
		memset(visited, false, sizeof(visited));
		queue < pair<pair<int, int>, int>> q; // i,j, 걸린시간

		for (int i = 0; i < selectV.size(); i++) { // 퍼트릴 바이러스
			if (selectV[i]) {
				q.push({ {v[i].first,v[i].second},0 });
				visited[v[i].first][v[i].second] = true;
			}
		}

		int finish = 0;

		while (!q.empty()) {
			pair<int, int> cur = q.front().first;
			int time = q.front().second;
			q.pop();

			if(arr[cur.first][cur.second]==2) {}
			else if (time > finish) finish = time; // 걸린 시간

			for (int dir = 0; dir < 4; dir++) {
				int nx = dx[dir] + cur.first;
				int ny = dy[dir] + cur.second;

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (!visited[nx][ny] && arr[nx][ny] != 1) { // 벽이 아니고 방문하지 않았다면
					visited[nx][ny] = true;
					q.push({ {nx,ny}, time + 1 });
				}
			}
		}

		bool chk = true;
		// 모든 빈칸에 퍼트리지 못했다면
		for (int i = 0; i < n; i++) {
			if (!chk) break;
			for (int j = 0; j < n; j++) {
				if (!visited[i][j] && arr[i][j] == 0) { // 빈칸인데 방문을 못했다면
					chk = false;
					break;
				}
			}
		}

		if (chk) { // 다 퍼트렸다면
			if (finalTime > finish) finalTime = finish; // 최소 시간으로 업데이트
		}

	} while (next_permutation(selectV.begin(), selectV.end()));

	if (finalTime != 98765432) cout << finalTime;
	else cout << -1;
}
```