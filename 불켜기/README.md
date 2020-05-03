

## 불켜기(문제 _ [11967](https://www.acmicpc.net/problem/11967))

농부 존은 최근에 N*N개의 방이 있는 거대한 헛간을 새로 지었다. 각 방은 (1, 1)부터 (N,N)까지 번호가 매겨져있다(2≤N≤100). 어둠을 무서워하는 암소 베시는 최대한 많은 방에 불을 밝히고 싶어한다.

베시는 유일하게 불이 켜져있는 방인 (1,1)방에서 출발한다. 어떤 방에는 다른 방의 불을 끄고 켤 수 있는 스위치가 달려있다. 예를 들어, (1, 1)방에 있는 스위치로 (1, 2)방의 불을 끄고 켤 수 있다. 

**베시는 불이 켜져있는 방으로만 들어갈 수 있고, 각 방에서는 상하좌우에 인접한 방으로 움직일 수 있다.**

베시가 불을 켤 수 있는 방의 최대 개수를 구하시오.


## 입력과 출력

**입력**
첫 번째 줄에는 N(2≤N≤100)과, M(1≤M≤20,000)이 정수로 주어진다.

다음 M줄에는 네 개의 정수 x, y, a, b가 주어진다. (x, y)방에서 (a, b)방의 불을 켜고 끌 수 있다는 의미이다. 한 방에 여러개의 스위치가 있을 수 있고, 하나의 불을 조절하는 스위치 역시 여러개 있을 수 있다. 

**출력**
베시가 불을 켤 수 있는 방의 최대 개수를 출력하시오.

## 예제

    3 6
    1 1 1 2
    2 1 2 2
    1 1 1 3
    2 3 3 1
    1 3 1 2
    1 3 2 1

    answer : 5

## 풀이
각 방이 1,1 ~ n,n까지 번호가 매겨져있기 때문에 인덱스를 1,1부터 n,n 까지 사용한다. 즉 n이 5라면 arr[5][5]까지 사용해야 한다. 그렇기 때문에 nx,ny 의 범위체크를 다른 문제와 다르게 해줘야 했다. 또한 for문에서 행,열 모두 0부터가 아닌 1부터 사용했다.

베시는 불이 켜져 있는 방으로만 들어갈 수 있고, 베시는 이미 방문했던 방도 다시 되돌아 갈 수 있다. 

그렇기 때문에 새로운 불을 킬 때마다 visited 배열을 초기화하는 과정이 필요로 했다. 

해당 방에 있는 스위치들은 list 배열을 이용해 저장했고, 불을 킬 때마다 배열에서 값들을 삭제했다. 삭제하지 않으면 이미 킨 불을 계속 키기 때문에 무한루프에 빠지게 된다.


## 코드

```cpp
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
```