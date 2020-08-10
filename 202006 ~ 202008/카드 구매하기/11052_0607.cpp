
#include <iostream>
#include <algorithm>
using namespace std;

int dp[1001];
int a[1001];
int main(){
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    
    for(int i=1;i<=n;i++){ // 1번카드팩 ~ n번카드팩
        for(int j=i;j<=n;j++){ //카드를 1장 ~n장 사는 경우
            dp[j] = max(dp[j-i]+a[i],dp[j]);
        }
    }
    cout << dp[n];
}