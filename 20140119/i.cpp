#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Point;
#define x first
#define y second
const int N = 55;
const int M = N * N;
Point vec[N];
int dp[N][M];

bool cmp(const Point &a, const Point &b) { return a.y * b.x > a.x * b.y; }
void update(int &a, int b) { a = max(b, a); }

int main() {
	int _, n, k;
	ios::sync_with_stdio(0);
	cin >> _;
	for (int cas = 1; cas <= _; cas++) {
		cin >> n >> k;
		for (int i = 0; i < n; i++) cin >> vec[i].x >> vec[i].y;
		int sum = 0;
		for (int i = 0; i < n; i++) sum += vec[i].y;
		sort(vec, vec + n, cmp);
		memset(dp, 0x80, sizeof(dp));
		dp[0][0] = 0;
		for (int i = 0; i < n; i++) {
			for (int k = i + 1; k > 0; k--) {
				for (int j = sum; j >= vec[i].y; j--) {
					if (dp[k - 1][j - vec[i].y] != 0x80808080) {
						update(dp[k][j], dp[k - 1][j - vec[i].y] + ((j << 1) - vec[i].y) * vec[i].x);
					}
				}
			}
		}
		int ans = 0x80808080;
		for (int i = 0; i <= k; i++) for (int j = 0; j <= sum; j++) update(ans, dp[i][j]);
		cout << "Case " << cas << ": " << ans << endl;
	}
	return 0;
}

