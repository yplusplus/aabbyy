#include <bits/stdc++.h>
using namespace std;

const int N = 11;
const int M = 33;
const int INF = 0x77777777;
typedef long long LL;

LL p[N], k[N][M], c[N], s[M];

int main() {
	ios::sync_with_stdio(0);
	int _, n, m;
	cin >> _;
	while (_--) {
		cin >> n >> m;
		LL ans = 0;
		for (int i = 0; i < n; i++) {
			cin >> c[i];
			for (int j = 0; j < c[i]; j++) cin >> k[i][j];
			cin >> p[i];
		}
		for (int i = 0; i < m; i++) cin >> s[i];
		for (int i = 0; i < n; i++) {
			LL mn = INF;
			for (int j = 0; j < c[i]; j++) mn = min(s[k[i][j] - 1], mn);
			ans += mn * p[i];
		}
		cout << ans << endl;
	}
	return 0;
}
