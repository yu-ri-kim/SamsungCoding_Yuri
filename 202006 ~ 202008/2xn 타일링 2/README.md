
## 2×n 타일링 2(문제 _ [11727](https://www.acmicpc.net/problem/11727))

2×n 직사각형을 1×2, 2×1과 2×2 타일로 채우는 방법의 수를 구하는 프로그램을 작성하시오.

**입력**
첫째 줄에 n이 주어진다. (1 ≤ n ≤ 1,000)

**출력**
첫째 줄에 2×n 크기의 직사각형을 채우는 방법의 수를 10,007로 나눈 나머지를 출력한다.

## 예제

	12
	[answer] 2731

## 풀이

![1](https://user-images.githubusercontent.com/63140456/83495720-0d938000-a4f3-11ea-89c1-b4935b9edb86.jpg)
![2](https://user-images.githubusercontent.com/63140456/83495728-0ec4ad00-a4f3-11ea-9451-acb0b110d457.jpg)


## 코드

```cpp
int dp[1001];
int main() {
	int n;
	cin >> n;
	dp[1] = 1; dp[2] = 3;

	for (int i = 3; i <= n; i++) {
		dp[i] = (dp[i - 1] + dp[i - 2] * 2) % 10007;
	}
	cout << dp[n] % 10007;
}
```