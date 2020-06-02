#include <iostream>
#include <queue>
using namespace std;

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
string arr[51];
bool visited[51][51];
int maxHour;

void init(int h,int w){
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            visited[i][j]= false;
        }
    }
}

int main(){
    int h, w;
    cin >> h >> w; // 세로와 가로

    for(int i=0; i< h; i++){
         cin >> arr[i];
    }

    // 각 육지마다 bfs를 돌고,
    // 제일 오래 걸리는 위치 max 로 저장.

    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(arr[i][j]=='L'){ // bfs 시작
                init(h,w); // visited initialize

                queue<pair<pair<int,int>, int> > q;
                q.push(make_pair(make_pair(i,j),0));
                visited[i][j]=true;

                while(!q.empty()){
                    pair<int,int> cur = q.front().first;
                    int distance = q.front().second;
                    if(maxHour < distance) maxHour = distance; // 가장 먼 곳

                    q.pop();

                    for(int dir=0;dir<4;dir++){
                        int nx = cur.first + dx[dir];
                        int ny = cur.second + dy[dir];

                        if(nx < 0 || nx >=h || ny<0 || ny>=w) continue;

                        if(arr[nx][ny] == 'L' && !visited[nx][ny]){
                            visited[nx][ny] = true;
                            q.push(make_pair(make_pair(nx,ny),distance+1));
                        }
                    }
                }
            }
        }
    }

    cout << maxHour;
}
