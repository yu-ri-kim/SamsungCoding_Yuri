
#include <iostream>
#include <algorithm>
using namespace std;

int arr[1001][3];
int dp[1001][3]; // i번째 집이 빨,초,파로 칠했을 때의 최솟값
int n;

int main() {
	ios::sync_with_stdio(0);
	cout.tie(0); cin.tie(0);
	cin >> n;

	for (int i = 0; i < n; i++) // 빨, 초, 파
    {   
		cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
	}

	dp[0][0] = arr[0][0]; dp[0][1] = arr[0][1]; dp[0][2] = arr[0][2];

	for (int i = 1; i < n; i++) 
    {
		dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + arr[i][0]; // 빨간색으로 칠할 경우
		dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + arr[i][1]; // 초록색으로 칠할 경우
		dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + arr[i][2]; // 파란색으로 칠할 경우
	}

	cout << min({ dp[n - 1][0],dp[n - 1][1],dp[n - 1][2] });
}