#include <iostream>
#include <vector>
using namespace std;

vector<int> dp(11);
vector<int> dp2(11);

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < 10; i++) dp[i] = 1; 
	dp[10] = 10; // dp[0]~dp[9]까지의 합

	for (int i = 2; i <= n; i++) { // n이 2일때부터
		dp2[0] = dp[10] % 10007;
		long long sum = dp2[0];

		for (int i = 1; i < 10; i++) {
			if (dp[i - 1] > dp2[i - 1]) { // 더 크다면
				dp2[i] = ((dp2[i - 1]+10007) - dp[i - 1]) % 10007; // 더해주고 뺀다
			}
			else dp2[i] = (dp2[i - 1] - dp[i - 1]) % 10007;
			sum += dp2[i]; // 새로운 합
		}
		dp2[10] = sum % 10007;
		dp = dp2; 
	}
	cout << dp[10] % 10007;
}