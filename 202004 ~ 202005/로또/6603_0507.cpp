#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

bool isused[50];
int arr[6];
vector<int> datas;

void func(int k) {
	if (k == 6) { // 6개를 뽑았다면 출력한다
		for (int i = 0; i < 6; i++) {
			cout << arr[i] << " ";
		}
		cout << '\n';
		return;
	}

	for (int i = 0; i < datas.size(); i++) {
		int next = datas[i]; // 뽑은 수
		
		if (!isused[next]) { // 아직 수열에 사용하지 않았다면
			if (k == 0 || arr[k - 1] < next) { // 비 내림차순 조건
				arr[k] = next; // 수열에 넣는다
				isused[next] = true; // 사용했다고 표시한다
				func(k + 1); // 다음 숫자를 뽑으러 간다
				isused[next] = false; // 더이상 사용하지 않는다
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int k;
	do{
		cin >> k;

		int tmp;
		for (int i = 0; i < k; i++) {
			cin >> tmp;
			datas.push_back(tmp);
		}
		// n개에서 m개 뽑기. 비 내림차순
		// 같은 수열 여러번 출력 불가

		func(0);

		// 사용한 배열들 초기화
		datas.clear();
		memset(arr, 0, sizeof(arr));
		memset(isused, false, sizeof(isused));

		cout << '\n'; // 각 케이스 사이에는 빈 줄을 출력한다.

	} while (k != 0); // k가 0이라면 그만한다.
}