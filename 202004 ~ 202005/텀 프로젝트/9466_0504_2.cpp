#include <iostream>
#include <string.h>

using namespace std;

int arr[100001];
bool visited[100001];
bool finished[100001];
int cnt;

void dfs(int cur){
    visited[cur]= true;
    int next = arr[cur];

    if(!visited[next]){
        dfs(next);
    }
    else{
        if(!finished[next]){
            for(int i=next;i != cur ; i=arr[i]){ // 사이클 돈다
            // 그 다음부터 현재로 돌아올때까지
                cnt++;
            }
            cnt ++;
        }
    }
    finished[cur]=true;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for(int test=0;test<t;test++){
        int n;
        cin >> n;

        for(int i=1;i<=n;i++){ //1번부터 n번까지
            cin >> arr[i];
        }

        memset(visited, false, sizeof(visited));
        memset(finished, false, sizeof(finished));

        cnt = 0; // 팀을 형성한 학생들

        for(int i=1;i<=n;i++){
            if(!visited[i]) dfs(i);
        }

        cout << n - cnt<<"\n";

    }
}
