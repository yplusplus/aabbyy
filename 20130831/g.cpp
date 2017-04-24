#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> PII;
const int N = 33;
PII pb[N];

int main() {
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; i++) cin >> pb[i].first, pb[i].second = i + 1;
		sort(pb, pb + n);
		int tm = 0, pn = 0, c = 0;
		for (int i = 0; i < n; i++) {
			tm += pb[i].first;
			if (tm > 300) break;
			c++, pn += tm;
		}
		cout << c << ' ' << pn << endl;
		for (int i = 0; i < c; i++) cout << pb[i].second << endl;
	}
	return 0;
}


