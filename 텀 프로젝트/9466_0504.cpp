
// 시간 초과 코드

#include <iostream>
#include <stack>

using namespace std;

int arr[100001];
bool visited[100001];

void init(int n){
    for(int i=1;i<=n;i++){
        visited[i]=false;
    }
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
            // 선택한 학생들의 번호가 주어짐
            cin >> arr[i];
        }
        init(n); // visited 초기화
        int cnt = 0;

        for(int i=1;i<=n;i++){
            bool chk = false;
            init(n); // visited 초기화
            stack<int> s;
            s.push(i);
            visited[i] = true;
            
            while(!s.empty()){
                int cur = s.top();
                s.pop();

                int next = arr[cur];

                if(next == i){ // 사이클 형성
                    chk = true;
                    break;
                }
                if(!visited[next]){
                    s.push(next);
                    visited[next] = true;
                }
            }
            if(!chk) {
                cnt ++ ; // stack이 empty이면 팀을 이루지 못함
               // cout << "i: " << i << endl;
            }
        }
        cout << cnt;
    }
}
