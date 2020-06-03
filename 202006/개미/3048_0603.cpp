#include <iostream>
#include <list>
using namespace std;

int n1, n2, t;
int main() {
	cin >> n1 >> n2;
	list<pair<int, char>> l;

	string tmp;
	cin >> tmp;
	for (char c : tmp) {
		l.push_front({ 0,c });
	}

	cin >> tmp;
	for (char c : tmp) {
		l.push_back({ 1,c });
	}

	cin >> t;

	list<pair<int, char>>::iterator iter;

	while (t) {
		auto it2 = l.begin();
		auto it1 = it2++;
		auto e = l.end();

		for (; ;) {
			if ((*it1).first == 0 && (*it2).first == 1){
				swap(*it1, *it2); // 교환
				it1 = it2++;
				if (it2 == e) break;
				it1 = it2++;
				if (it2 == e) break;
			}
			else {
				it1 = it2++;
				if (it2 == e) break;
			}
		}
		t--;
	}

	for (auto i : l) {
		cout << i.second;
	}
}