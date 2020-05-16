#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> datas;
int l, c;
bool isused[27];
char arr[16];

// 자음 , 모음
void func(int k, int consonant, int vowel) {
	if (k == l && consonant >= 2 && vowel >= 1) { // l개 다 골랐다면
		for (int i = 0; i < l; i++) {
			cout << (char)arr[i];
		}
		cout << "\n";
		return;
	}

	for (int i = 0; i < datas.size(); i++) {
		char next = datas[i];

		if (!isused[next - 'a']) { // 수열에 없는 알파벳이라면
			if (k == 0 || arr[k - 1] < next) { // 증가순 수열
				if (next == 'a' || next == 'e' || next == 'i' || next == 'o' || next == 'u') { // 모음이라면
					isused[next - 'a'] = true;
					arr[k] = next;
					func(k + 1, consonant, vowel + 1);
					isused[next - 'a'] = false;
				}
				else { // 자음이라면
					isused[next - 'a'] = true;
					arr[k] = next;
					func(k + 1, consonant + 1, vowel);
					isused[next - 'a'] = false;
				}
			}
		}

	}
}
int main() {
	cin >> l >> c; // c개에서 l개뽑기
	for (int i = 0; i < c; i++) {
		char tmp;
		cin >> tmp;
		datas.push_back(tmp);
	}

	sort(datas.begin(), datas.end()); // 데이터 정렬
	func(0, 0, 0);
}