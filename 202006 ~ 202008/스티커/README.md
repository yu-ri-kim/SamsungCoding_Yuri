
## 스티커 (문제 _ [9465](https://www.acmicpc.net/problem/9465))

상근이의 여동생 상냥이는 문방구에서 스티커 2n개를 구매했다. 스티커는 그림 (a)와 같이 2행 n열로 배치되어 있다. 상냥이는 스티커를 이용해 책상을 꾸미려고 한다.

상냥이가 구매한 스티커의 품질은 매우 좋지 않다. **스티커 한 장을 떼면, 그 스티커와 변을 공유하는 스티커는 모두 찢어져서 사용할 수 없게 된다.** 즉, 뗀 스티커의 왼쪽, 오른쪽, 위, 아래에 있는 스티커는 사용할 수 없게 된다.

모든 스티커를 붙일 수 없게된 상냥이는 각 스티커에 점수를 매기고, 점수의 합이 최대가 되게 스티커를 떼어내려고 한다. 먼저, 그림 (b)와 같이 각 스티커에 점수를 매겼다. **상냥이가 뗄 수 있는 스티커의 점수의 최댓값을 구하는 프로그램을 작성하시오.** 즉, 2n개의 스티커 중에서 점수의 합이 최대가 되면서 서로 변을 공유 하지 않는 스티커 집합을 구해야 한다.

**입력**
첫째 줄에 테스트 케이스의 개수 T가 주어진다. 각 테스트 케이스의 첫째 줄에는 n (1 ≤ n ≤ 100,000)이 주어진다. 다음 두 줄에는 n개의 정수가 주어지며, 각 정수는 그 위치에 해당하는 스티커의 점수이다. 연속하는 두 정수 사이에는 빈 칸이 하나 있다. 점수는 0보다 크거나 같고, 100보다 작거나 같은 정수이다.

**출력**
각 테스트 케이스 마다, 2n개의 스티커 중에서 두 변을 공유하지 않는 스티커 점수의 최댓값을 출력한다.
  
## 예제

	2
	5
	50 10 100 20 40
	30 50 70 10 60
	7
	10 30 10 50 100 20 40
	20 40 30 50 60 20 80	
	
	< answer >
	260
	290

  

## 풀이

스티커의 점수가 음수인 경우가 없기 때문에 가장 간단하게 생각해보면 많은 스티커를 뗄 수 있다면 많은 점수를 얻을 수 있다

| v  |   |  v |  |v || v |  |
|--|--|--|--|--|--|--|--|
|  | v| |  v|  | v|  |  v|

1. 왼쪽 위부터  떼는 경우 - 대각선으로 떼면 가장 많이 뗄 수 있다.

|   | v  |   |v  | |v|  | v |
|--|--|--|--|--|--|--|--|
| v | | v|  |v  | | v |  |

2. 왼쪽 아래부터  떼는 경우 - 대각선으로 떼면 가장 많이 뗄 수 있다.

하지만 항상 저렇게 뗄 때 최고 점수를 얻는 것은 아니다

| 50  |   |  100  |   | 40  |
|--   |-- |--     |-- |--   |
|     | 50|       |  10| 60 |

이런 경우 50, 50, 100, 10, 40을 선택하면 50, 50, 100, 60을 선택했을 때보다 적은 점수를 얻게 된다

그렇기 때문에 바로 옆 대각선으로 가는 경우와, **두칸 옆 대각선**으로 가는 경우의 값을 비교하고 더 큰 값에 스티커를 떼야 한다.


			dp[0][1] = arr[0][1]; dp[1][1] = arr[1][1];
			
			for (int i = 2; i <= n; i++) {
				dp[0][i] = Math.max(dp[1][i-1], dp[1][i-2]) + arr[0][i];
				dp[1][i] = Math.max(dp[0][i-1], dp[0][i-2]) + arr[1][i];
			}

## 코드

```java
public class Main {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		StringTokenizer st;
		
		int tc = Integer.parseInt(br.readLine());
		int n = 0;
        
		while(tc-- > 0) {
			n = Integer.parseInt(br.readLine());
			int[][] arr = new int[2][n+1];
			int[][] dp = new int[2][n+1];
			
			for (int i = 0; i < 2; i++) {
				st = new StringTokenizer(br.readLine());
				
				for (int j = 1; j <= n; j++) {
					arr[i][j] = Integer.parseInt(st.nextToken());
				} // end of input
			}
			
			dp[0][1] = arr[0][1]; dp[1][1] = arr[1][1];
			
			for (int i = 2; i <= n; i++) {
				dp[0][i] = Math.max(dp[1][i-1], dp[1][i-2]) + arr[0][i];
				dp[1][i] = Math.max(dp[0][i-1], dp[0][i-2]) + arr[1][i];
			}
			
			sb.append(Math.max(dp[0][n], dp[1][n])).append("\n");
			
		} // end of tc
		
		System.out.println(sb);
	} // end of main
}

```
