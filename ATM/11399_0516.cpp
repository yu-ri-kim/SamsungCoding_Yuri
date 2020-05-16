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

    sort(datas.begin(), datas.end());

    dp[0]= datas[0];
    int sum = dp[0];

    for(int i=1;i<n;i++){
        dp[i] = dp[i-1] + datas[i];
        sum += dp[i];
    }
    
    cout << sum;
}