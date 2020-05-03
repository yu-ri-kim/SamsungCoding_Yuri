#include <iostream>
#include <list>
#include <queue>

using namespace std;

int arr[101][101];
bool visited[101][101];
bool light[101][101];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
list<pair<int,int > > lightList[101][101];

int getMaxCnt(int n){ // 불 켜진 개수 리턴
    int cnt = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(light[i][j]== true){
                cnt++;
            }
        }
    }
    return cnt;
}

void init(int n){ // visited 초기화
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            visited[i][j]=false;
        }
    }
}

int main(){
    int n, m;
    cin >> n >> m;

    for(int i=0;i<m;i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        lightList[x1][y1].push_back(make_pair(x2,y2)); // 스위치 리스트 형태로 저장
    }
        
    light[1][1]= true; // 시작하는 방은 불이 켜져있다.
    visited[1][1]=true;

    for(auto cur : lightList[1][1]){ // 스위치로 불켜주기
        light[cur.first][cur.second] = true;
    }

    queue<pair<int, int > > q;
    q.push(make_pair(1,1));

    while(!q.empty()){
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();

        for(int dir=0;dir<4;dir++){
            int nx = curX + dx[dir];
            int ny = curY + dy[dir];

            // 인덱스를 1부터 n까지 사용
            if(nx < 1 || ny <  1 || nx > n || ny > n) continue;

            if(light[nx][ny] && !visited[nx][ny]){ // 불이 켜져있는 곳에만 접근 가능
                bool trig = false; // 불을 킨 곳이 있는지 확인
                
                while(lightList[nx][ny].size() > 0 ){
                    trig = true;
                    int curLx = lightList[nx][ny].front().first;
                    int curLy = lightList[nx][ny].front().second;
                    
                    light[curLx][curLy] = true; // 불키기
                    lightList[nx][ny].pop_front(); // 이미 킨 스위치는 삭제해주기
                }
                
                if(trig) { // 하나라도 불을 켜줬다면
                    init(n);
                }
                
                visited[nx][ny]= true;
                q.push(make_pair(nx,ny));
            }
        }
    }
    cout << getMaxCnt(n);
    
}
