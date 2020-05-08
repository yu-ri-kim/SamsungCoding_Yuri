
#include <iostream>
#include <list>
using namespace std;

list<pair<int,int>> bridge; // 남은 시간, 무게
int time; // 걸린 시간
int arr[1001];
int n, w, l; //다리를 건너는 트럭의 수, 다리의 길이, 다리의 최대 하중

int main() {
	cin >> n >> w >> l;
	for (int i = 0; i < n; i++) {
		cin >> arr[i]; // i번째 다리의 무게
	}

	int next = 0; // 다음 들어가야 하는 트럭
	int h = 0; // 현재 다리 무게
	int done = 0; // 나간 트럭의 수

	while (done != n) { // 모든 트럭이 나갈 동안
		for (auto iter = bridge.begin(); iter != bridge.end(); ) { 
			if ((*iter).first == 0) { // 이제 다리를 벗어나는 트럭
				h -= (*iter).second;
				iter = bridge.erase(iter);
				done++; // 나간 트럭의 수 증가
			}
			else { // 다리에 있는 트럭
				if ((*iter).first > 0) (*iter).first--;
				iter++;
			}
		}
		if (arr[next] + h <= l) { // 다리가 올라가도 괜찮다면
			bridge.push_back({ w - 1,arr[next] }); // 올라간 순간 1초 제거
			h += arr[next];
			next++;
		}
		time++; // 시간 증가
	}
	cout << time;
}