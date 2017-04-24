#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<int, int> PII;
typedef vector<PII> VII;
const int N = 51;
const int M = 500001;
const DB EPS = 1e-8;

VII temp;
DB dp[N][M], m;
int ans[N], a[N], b[N];
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }

int run() {
	int n;
	while (cin >> n >> m) {
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j < M; ++j) dp[i][j] = DBL_MAX;
		}
		dp[0][0] = m;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i] >> b[i];
			for (int j = 0; j < M; ++j) {
				dp[i][j] = min(dp[i - 1][j] * (1 - b[i] / 100.0), dp[i][j]);
				if (j - a[i] >= 0) dp[i][j] = min(dp[i - 1][j - a[i]], dp[i][j]);
			}
		}
		int mark = 0;
		for (int i = 0; i < M; ++i) {
			if (dp[n][mark] - mark > dp[n][i] - i) mark = i;
		}
		//cout << dp[n][mark] << ' ' << dp[n][30] << endl;
		//cout << mark << endl;
		for (int i = n; i >= 1; --i) {
			if (sgn(dp[i][mark] - dp[i - 1][mark] * (1 - b[i] / 100.0))) ans[i] = 2, mark -= a[i];
			else ans[i] = 1;
		}
		temp.resize(n);
		for (int i = 1; i <= n; ++i) temp[i - 1] = PII(ans[i], i);
		sort(temp.begin(), temp.end());
		for (int i = 0; i < n; ++i) {
			cout << temp[i].second << ' ';
			if (temp[i].first == 1) cout << "reverse" << endl;
			else cout << "front" << endl;
		}
	}
	return 0;
}

int main() {
	freopen("discount.in", "r", stdin);
	freopen("discount.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
