#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
#define x first
#define y second
const int N = 1111;
PII tech[N];

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	int _, n ,d, m, p, k, v, t1, t2;
	cin >> _;
	while (_--) {
		cin >> n >> d >> m >> p >> k >> v >> t1 >> t2;
		t1 *= v; t2 *= v; m *= p;
		for (int i = 0; i < n; i++) cin >> tech[i].x >> tech[i].y;
		sort(tech, tech + n);
		int best = 0;
		for (int i = 0; i <= n; i++) {
			int sum = 0, pos = k;
			for (int j = 0; ; j++) {
				if (j == i) {
					pos += t2;
					sum += m / (pos * pos);
				}
				if (j >= n) break;
				if (pos + t1 <= tech[j].y) {
					pos = max(pos + t1, tech[j].x);
					sum += d;
				}
			}
			best = max(sum, best);
		}
		cout << best << endl;
	}
	return 0;
}

