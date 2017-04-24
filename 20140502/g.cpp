#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
#define x first
#define y second
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
inline DB pt2line(const Point &p, const Point &a, const Point &b) { return fabs(cross(a - p, b - p) / sqrt(dot(b - a, b - a))); }

const int N = 1 << 8;
const DB EPS = 1e-8;
inline int sgn(const DB &a) { return (a > EPS) - (a < -EPS); }
Point a, b, c, d, city[N];
DB dp[N][N << 1], price[N];
int ans[N];
void get(Point &a) { cin >> a.x >> a.y; }

int run() {
	int n, m;
	while (cin >> n >> m) {
		get(a); get(b);
		get(c); get(d);
		for (int i = 0; i <= n; ++i) {
			for (int j = -n - 2; j <= n + 2; ++j) dp[i][j + N] = FLT_MAX;
		}
		dp[0][N] = 0;
		for (int i = 1; i <= n; ++i) {
			get(city[i]);
			cin >> price[i];
			DB d1 = pt2line(city[i], a, b);
			DB d2 = pt2line(city[i], c, d);
			//cout << d1 * price[i] << ' ' << d2 * price[i] << endl;
			for (int j = -n; j <= n; ++j) {
				int t = j + N;
				dp[i][t] = min(dp[i - 1][t + 1] + d1 * price[i], dp[i][t]);
				dp[i][t] = min(dp[i - 1][t - 1] + d2 * price[i], dp[i][t]);
				//cout.width(15); cout << dp[i][t] << ' ';
			}
			//cout << endl;
		}
		int mark = N;
		for (int i = -m; i <= m; ++i) {
			int t = i + N;
			if (dp[n][t] < dp[n][mark]) mark = t;
		}
		//cout << "different " << (mark - N) << endl;
		for (int i = n; i >= 1; --i) {
			DB d = pt2line(city[i], a, b);
			if (sgn(dp[i - 1][mark + 1] + d * price[i] - dp[i][mark]) == 0) {
				ans[i] = 1;
				++mark;
			} else {
				ans[i] = 2;
				--mark;
			}
			//cout << mark << endl;
		}
		for (int i = 1; i <= n; ++i) {
			if (i != 1) cout.put(' ');
			cout << ans[i];
		}
		cout << endl << endl;
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
