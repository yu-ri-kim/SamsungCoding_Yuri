## 암호 만들기(문제 _ [1759](https://www.acmicpc.net/problem/1759))

바로 어제 최백준 조교가 방 열쇠를 주머니에 넣은 채 깜빡하고 서울로 가 버리는 황당한 상황에 직면한 조교들은, 702호에 새로운 보안 시스템을 설치하기로 하였다. 이 보안 시스템은 열쇠가 아닌 암호로 동작하게 되어 있는 시스템이다.

암호는 서로 다른 L개의 알파벳 소문자들로 구성되며 **최소 한 개의 모음(a, e, i, o, u)과 최소 두 개의 자음**으로 구성되어 있다고 알려져 있다. 또한 정렬된 문자열을 선호하는 조교들의 성향으로 미루어 보아 암호를 이루는 **알파벳이 암호에서 증가하는 순서**로 배열되었을 것이라고 추측된다. 즉, abc는 가능성이 있는 암호이지만 bac는 그렇지 않다.

새 보안 시스템에서 조교들이 암호로 사용했을 법한 문자의 종류는 C가지가 있다고 한다. 이 알파벳을 입수한 민식, 영식 형제는 조교들의 방에 침투하기 위해 암호를 추측해 보려고 한다. C개의 문자들이 모두 주어졌을 때, 가능성 있는 암호들을 모두 구하는 프로그램을 작성하시오.

**입력**
첫째 줄에 두 정수 L, C가 주어진다. (3 ≤ L ≤ C ≤ 15) 다음 줄에는 C개의 문자들이 공백으로 구분되어 주어진다. 주어지는 문자들은 알파벳 소문자이며, 중복되는 것은 없다.

**출력**
각 줄에 하나씩, 사전식으로 가능성 있는 암호를 모두 출력한다.

 
## 예제

	4 6
	a t c i s w

	answer :
	acis
	acit
	aciw
	acst
	acsw
	actw
	aist
	aisw
	aitw
	astw
	cist
	cisw
	citw
	istw


## 풀이

백트래킹을 이용해 소문자 알파벳 26개에서 l개(암호의 길이)를 뽑아내는 형식의 문제이다.

이때 모든 수열은 사전순으로 출력되어야 하고, 비 내림차순이어야 하는 조건이 있다.

또한 최소 한개의 모음, 두개의 자음이 사용되어야 한다

1.  사전순 출력 : vector datas가 오름차순 정렬이 되어있어야 한다 -> sort()
    
2.  비 내림차순 : 수열에 값을 넣을 때, 이미 들어와 있는 값보다 큰 값만 넣는다
> if (k == 0 || arr[k - 1] < next)

3.  순서가 다르지만 같은 값을 가진 수열은 같은 수열 : bool isused[] 을 이용해 이미 사용한 값은 수열에 넣지 않는다.

4. 최소 한개의 모음, 두개의 자음 사용 : func() 함수를 수행할 때 수열에 넣은 모음과 자음의 개수를 같이 전달한다
> void func(int k, int consonant, int vowel)

## 코드
```cpp
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
```
