#include <algorithm>
#include <iostream>
using namespace std;

typedef pair<int, int> PII;
#define x first
#define y second
const int N = 1111;
PII a[N];

int main() {
	ios::sync_with_stdio(0);
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; i++) {
			cin >> a[i].x;
			a[i].y = i + 1;
		}
		sort(a, a + n);
		a[n] = PII(N, N);
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (a[i].x <= i + 1 && i + 2 < a[i + 1].x) cnt++;
		}
		cout << cnt << endl;
		for (int i = 0; i < n; i++) {
			if (a[i].x <= i + 1 && i + 2 < a[i + 1].x) {
				cout << i + 1;
				for (int j = 0; j <= i; j++) cout << ' ' << a[j].y;
				cout << endl;
			}
		}
	}
	return 0;
}
