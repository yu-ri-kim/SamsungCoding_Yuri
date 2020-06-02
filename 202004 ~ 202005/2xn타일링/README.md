
## 2xn 타일링(문제 _ [11726](https://www.acmicpc.net/problem/11726))

2×n 크기의 직사각형을 1×2, 2×1 타일로 채우는 방법의 수를 구하는 프로그램을 작성하시오.

아래 그림은 2×5 크기의 직사각형을 채운 한 가지 방법의 예이다.

**입력**
첫째 줄에 n이 주어진다. (1 ≤ n ≤ 1,000)

**출력**
첫째 줄에 2×n 크기의 직사각형을 채우는 방법의 수를 10,007로 나눈 나머지를 출력한다. 

## 예제

	
	9
	answer : 55

  

## 풀이

참고 : [https://assb.tistory.com/33](https://assb.tistory.com/33)


## 코드

```cpp
int dp[1001];
int n;

int main(){
    cin >> n;
    
    dp[1]=1; dp[2]=2;
    
    for(int i=3;i<=n;i++){
        dp[i]= (dp[i-2] + dp[i-1]) % 10007;
    }
    
    cout << dp[n];
}
```