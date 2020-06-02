
## 맥주 마시면서 걸어가기(문제 _ [9205](https://www.acmicpc.net/problem/9205))

송도에 사는 상근이와 친구들은 송도에서 열리는 펜타포트 락 페스티벌에 가려고 한다. 올해는 맥주를 마시면서 걸어가기로 했다. 출발은 상근이네 집에서 하고, 맥주 한 박스를 들고 출발한다. **맥주 한 박스에는 맥주가 20개 들어있다. 목이 마르면 안되기 때문에 50미터에 한 병씩 마시려고 한다.**

상근이의 집에서 페스티벌이 열리는 곳은 매우 먼 거리이다. 따라서, 맥주를 더 구매해야 할 수도 있다. 미리 인터넷으로 조사를 해보니 다행히도 맥주를 파는 편의점이 있다. 편의점에 들렸을 때, 빈 병은 버리고 새 맥주 병을 살 수 있다. **하지만, 박스에 들어있는 맥주는 20병을 넘을 수 없다.**

편의점, 상근이네 집, 펜타포트 락 페스티벌의 좌표가 주어진다. 상근이와 친구들이 행복하게 페스티벌에 도착할 수 있는지 구하는 프로그램을 작성하시오.

**입력**
첫째 줄에 테스트 케이스의 개수 t가 주어진다. (t ≤ 50)

각 테스트 케이스의 첫째 줄에는 맥주를 파는 편의점의 개수 n이 주어진다. (0 ≤ n ≤ 100).

다음 n+2개 줄에는 상근이네 집, 편의점, 펜타포트 락 페스티벌 좌표가 주어진다. 각 좌표는 두 정수 x와 y로 이루어져 있다. (두 값 모두 미터, -32768 ≤ x, y ≤ 32767)

**송도는 직사각형 모양으로 생긴 도시이다. 두 좌표 사이의 거리는 x 좌표의 차이 + y 좌표의 차이 이다. (맨해튼 거리)**

**출력**
각 테스트 케이스에 대해서 상근이와 친구들이 행복하게 페스티벌에 갈 수 있으면 "happy", 중간에 맥주가 바닥나면 "sad"를 출력한다.

## 예제

	2
	2
	0 0
	1000 0
	1000 1000
	2000 1000
	2
	0 0
	1000 0
	2000 1000
	2000 2000
	
	[answer]
	happy
	sad

  

## 풀이
사실 더 간단하게 풀 수 있을 것 같지만, 아무튼 나는 이렇게 풀었다.

1. 먼저 집, 편의점, 페스티벌의 위치를 입력받는다. (arr)
2. 모든 장소끼리 거리를 계산한다.

![1](https://user-images.githubusercontent.com/63140456/82997004-c3b52080-a040-11ea-9bbe-a54f13527911.png)

4. 집에서 페스티벌로 가는 모든 경로를 검사하고,
5. 만약 페스티벌에 도착했다면 happy, 도착하지 못했다면 sad를 출력한다.

		<집에서 페스티벌로 가는 모든 경로 검사 방법>
		
		queue <pair<int,int>> q;
		q.push({ 0,1000 }); // 출발지(arr의 index) 1000(갈 수 있는 거리)
		visited[0] = true; // 출발지를 방문

		while (!q.empty()) {
			int cur = q.front().first; // 현재 위치의 index
			int curDist = q.front().second; // 현재 갈 수 있는 최대 거리
			q.pop();

			for (int test = 0; test < n + 2; test++) { // 모든 장소 검사(다 연결되어 있기 때문에)
				if (visited[test]) continue; // 이미 간 장소라면 continue

				int diff = dist[cur][test]; // 현재 장소와 다음 장소 사이의 거리
				if (curDist - diff >= 0) { // 갈 수 있는 거리라면 
					visited[test] = true; // 방문 체크
					int newDist = curDist - diff + 1000; // 다시 맥주 리필
					if (newDist > 1000) newDist = 1000; // 1000까지밖에 못감
					q.push({ test, newDist }); // 다시 탐색 시작
				}
			}
		}
		


## 코드

```cpp
string zzzzz = "";
int t, n;

int main() {
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);

	cin >> t;

	for (int i = 0; i < t; i++) {
		pair<int, int> arr[103];
		int dist[103][103];
		bool visited[103] = { false, };
		pair<int, int> tmp;

		cin >> n;

		// 거리 값 입력
		for (int j = 0; j < n+2; j++) {
			cin >> tmp.first >> tmp.second;
			arr[j] = tmp;
		}

		// 두 장소간 거리
		for (int k = 0; k < n + 2; k++) { 
			for (int h =0; h < n + 2; h++) { 
				dist[k][h] = abs(arr[k].first - arr[h].first)+abs(arr[k].second - arr[h].second);
			}
		}

		queue <pair<int,int>> q;
		q.push({ 0,1000 }); // 출발지,1000
		visited[0] = true;

		while (!q.empty()) {
			int cur = q.front().first;
			int curDist = q.front().second;
			q.pop();

			for (int test = 0; test < n + 2; test++) {
				if (visited[test]) continue;

				int diff = dist[cur][test]; // cur과 test사이의 거리
				if (curDist - diff >= 0) { // 갈 수 있는 거리라면 
					visited[test] = true;
					int newDist = curDist - diff + 1000;
					if (newDist > 1000) newDist = 1000; // 맥주 리필
					q.push({ test, newDist });
				}
			}
		}
		if (visited[n + 1]) zzzzz = zzzzz + "happy\n";
		else zzzzz += "sad\n";
	}
	cout << zzzzz;
}
```