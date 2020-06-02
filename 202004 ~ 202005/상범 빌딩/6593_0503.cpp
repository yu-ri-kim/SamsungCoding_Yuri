#include <iostream>
#include <queue>

// z , x,  y
bool visited[31][31][31];
char arr[31][31][31];
int dx[6] = { 1,0,-1,0,0,0 };
int dy[6] = { 0,1,0,-1,0,0 };
int dz[6] = { 0,0,0,0,-1,1 };

using namespace std;

void init(int l,int r, int c) {
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < r; j++) {
			for (int k = 0; k < c; k++) {
				arr[i][j][k] = '0';
				visited[i][j][k] = false;
			}
		}
	}
}

int main() {
	int l, r, c;

	while (1) {
		bool chk = false;

		cin >> l >> r >> c;

		if (!l && !r && !c) break; // 모두 0이라면 그만한다

		init(l, r, c); // 배열 초기화
		
		// 거리 , z, x, y
		pair<pair<int,int>, pair<int, int>> start;
		pair<pair<int, int>, pair<int, int>> end;

		// s은 시작, #은 금, .은 비어있는 칸, E는 출구
        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < r; j++)
            {
                for (int k = 0; k < c; k++)
                {
                    cin >> arr[i][j][k];
					if (arr[i][j][k] == 'S') {
						start = { {0,i},{j,k} }; // 시작점
					}
					if (arr[i][j][k] == 'E') {
						end = { {0,i},{j,k} }; // 출구
					}
                }
            }
        }
		
		// 거리, z , x , y
		queue<pair<pair<int, int>, pair<int, int>>> q;
		q.push(start);
		visited[start.first.second][start.second.first][start.second.second] = true;

		while (!q.empty()) {
			int curZ = q.front().first.second;
			int curX = q.front().second.first;
			int curY = q.front().second.second;

			int dist = q.front().first.first; // 거리

			q.pop();
			if (end.first.second == curZ && end.second.first == curX && end.second.second == curY) {
				cout << "Escaped in " << dist << " minute(s)." << "\n";
				chk = true;
				break;
			}

			for (int dir = 0; dir < 6; dir++) {
				int nz = curZ + dz[dir];
				int nx = curX + dx[dir];
				int ny = curY + dy[dir];

				if (nz < 0 || nz >= l || nx < 0 || nx >= r || ny < 0 || ny >= c) continue;

				if ((arr[nz][nx][ny] == 'E' ||arr[nz][nx][ny] == '.') && !visited[nz][nx][ny]) {
					visited[nz][nx][ny] = true;
					q.push({ { dist + 1, nz }, { nx,ny } });
				}
			}
		}

		if (!chk) cout << "Trapped!\n";
	}
}