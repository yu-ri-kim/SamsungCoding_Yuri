#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
vector<int> datas;
int dp[1001];

int main(){
    int n , tmp;
    cin >> n;

    for(int i=0;i<n;i++) {
        cin >> tmp;
        datas.push_back(tmp);
    }

    sort(datas.begin(), datas.end()); // 가장 작은 순으로 더해야 함

    dp[0]= datas[0];
    int sum = dp[0];

    for(int i=1;i<n;i++){
        dp[i] = dp[i-1] + datas[i]; // i-1까지 걸린 시간 + i가 걸리는 시간
        sum += dp[i]; // 최종 시간은 걸린 시간들의 합
    }
    
    cout << sum;
}
