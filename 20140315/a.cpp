#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PI2;
#define x first
#define y second

int run() {
	int n, d;
	while (cin >> n >> d) {
		VI w(n + 1), x(n + 1);
		set<PI2> cur;
		int mk1 = -1, mk2 = -1, ans = 0;
		for (int i = 1; i <= n; ++i) cin >> x[i] >> w[i];
		for (int i = 1, j = 1; i <= n; ++i) {
			while (x[i] - x[j] >= d) {
				cur.insert(PI2(-w[j], j));
				++j;
			}
			if (cur.empty()) continue;
			if (ans > cur.begin()->x - w[i]) {
				ans = cur.begin()->x - w[i];
				mk1 = cur.begin()->y;
				mk2 = i;
			}
		}
		//cout << ans << endl;
		cout << mk1 << ' ' << mk2 << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	return run();
}
