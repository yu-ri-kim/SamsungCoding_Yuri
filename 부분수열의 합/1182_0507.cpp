
#include <iostream>
using namespace std;

int arr[21];
int cnt; // 만족하는 부분수열의 개수

int main() {
	int n, s;
	cin >> n >> s;

	for (int i = 0; i < n; i++) cin >> arr[i];

	for (int i = 1; i < (1 << n); i++) { // 2^n승까지
		int sum = 0;
		int tmp = i; // 2로 나눌 수

		for (int j = 0; j < n; j++) {
			if (tmp % 2 == 1) { // arr[j] 선택 -> 부분 수열에 들어감
				sum += arr[j];
			}
			tmp /= 2; // 2로 나눈다. 다음에 선택할 거
		}
		if (sum == s) cnt++;
	}
	cout << cnt;
}