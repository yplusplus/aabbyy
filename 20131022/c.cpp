#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 111;
int a[N];

int main() {
	int n, avr;
	while (cin >> n) {
		avr = 0;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			a[i] *= n + 1;
			avr += a[i];
		}
		avr /= n + 1;
		int cnt = 0;
		for (int i = 0; i < n; i++) if (a[i] > avr) cnt += avr - a[i];
		for (int i = 0; i < n; i++) {
			if (i) cout << ' ';
			if (a[i] > avr) cout << 100 * (avr - a[i]) / cnt;
			else cout << 0;
		}
		cout << endl;
	}
	return 0;
}

