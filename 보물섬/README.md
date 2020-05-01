

## 보물섬(문제 _ [2589](https://www.acmicpc.net/problem/2589))

보물섬 지도를 발견한 후크 선장은 보물을 찾아나섰다. 보물섬 지도는 아래 그림과 같이 직사각형 모양이며 여러 칸으로 나뉘어져 있다. 각 칸은 육지(L)나 바다(W)로 표시되어 있다. 이 지도에서 이동은 상하좌우로 이웃한 육지로만 가능하며, 한 칸 이동하는데 한 시간이 걸린다. 

**보물은 서로 간에 최단 거리로 이동하는데 있어 가장 긴 시간이 걸리는 육지 두 곳에 나뉘어 묻혀있다.** 육지를 나타내는 두 곳 사이를 최단 거리로 이동하려면 같은 곳을 두 번 이상 지나가거나, 멀리 돌아가서는 안 된다.

![1](https://user-images.githubusercontent.com/63140456/80808430-881e6680-8bfa-11ea-9ff8-720aea95269e.jpg)

예를 들어 위와 같이 지도가 주어졌다면 보물은 아래 표시된 두 곳에 묻혀 있게 되고, 이 둘 사이의 최단 거리로 이동하는 시간은 8시간이 된다.

![2](https://user-images.githubusercontent.com/63140456/80808484-a08e8100-8bfa-11ea-9962-ef9e073bd557.jpg)

보물 지도가 주어질 때, 보물이 묻혀 있는 두 곳 간의 최단 거리로 이동하는 시간을 구하는 프로그램을 작성하시오.

## 입력과 출력

**입력**
첫째 줄에는 보물 지도의 세로의 크기와 가로의 크기가 빈칸을 사이에 두고 주어진다. 이어 L과 W로 표시된 보물 지도가 아래의 예와 같이 주어지며, 각 문자 사이에는 빈 칸이 없다. 보물 지도의 가로, 세로의 크기는 각각 50이하이다.

**출력**
첫째 줄에 보물이 묻혀 있는 두 곳 사이를 최단 거리로 이동하는 시간을 출력한다.

## 예제

	5 7
	WLLWWWL
	LLLWLLL
	LWLWLWW
	LWLWLLL
	WLLWLWW

    answer : 8

## 풀이
최단거리로 이동함에 있어 가장 긴 시간이 걸리는 육지 두 곳에 보물이 묻혀있기 때문에 각 출발점에서 모든 육지까지 최단거리를 계산해야 한다.

그러므로 육지에서 모든 부분을 시작점으로 생각하고 bfs를 돌리면 한 육지(모두 연결된)에서 모든 부분으로의 최단 거리가 나오게 된다. 

이때 가장 긴 시간이 걸려야 하기 때문에 max 변수를 이용해 매번 bfs를 진행할 때마다 거리 갱신을 해주면서 비교한다.

이때 실수하기 쉬운 점은 bfs를 시작하기전에 visited 배열을 초기화 해야 한다는 점이다. 


## 코드

```cpp
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
```