#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 111111;
const int D = 18;
const int INF = 0x77777777;
int arr[D][N], n;
LL sum[D][N];

#define lson l, m, d + 1
#define rson m + 1, r, d + 1
#define root 1, n, 0

void build(int l, int r, int d) {
	sort(arr[d] + l, arr[d] + r + 1);
	if (l == r) return ;
	int m = l + r >> 1;
	build(lson);
	build(rson);
}

void pre() {
	build(root);
	for (int i = 0; i < D; i++) {
		sum[i][0] = 0;
		for (int j = 1; j <= n; j++) sum[i][j] = sum[i][j - 1] + arr[i][j];
	}
}

int count(int L, int R, int v, int l, int r, int d) {
	int ret = 0;
	if (L <= l && r <= R) {
		ret = upper_bound(arr[d] + l, arr[d] + r + 1, v) - (arr[d] + l);
		return ret;
	}
	int m = l + r >> 1;
	if (L <= m) ret += count(L, R, v, lson);
	if (m < R) ret += count(L, R, v, rson);
	return ret;
}

LL getsum(int L, int R, int v, int l, int r, int d) {
	LL ret = 0;
	if (L <= l && r <= R) {
		int p = (int) (upper_bound(arr[d] + l, arr[d] + r + 1, v) - arr[d]);
		ret = (sum[d][r] - sum[d][p - 1] - (LL) v * (r - p + 1)) + ((LL) v * (p - l) - (sum[d][p - 1] - sum[d][l - 1]));
		return ret;
	}
	int m = l + r >> 1;
	if (L <= m) ret += getsum(L, R, v, lson);
	if (m < R) ret += getsum(L, R, v, rson);
	//cout << l << ' ' << r << ' ' << ret << endl;
	return ret;
}

int main() {
	//freopen("in", "r", stdin);
	int T, m;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d", &n);
		int mn = INF, mx = -INF;
		for (int i = 1; i <= n; i++) {
			scanf("%d", arr[0] + i);
			mn = min(mn, arr[0][i]), mx = max(mx, arr[0][i]);
			for (int j = 1; j < D; j++) arr[j][i] = arr[0][i];
		}
		pre();
		int x, y, v;
		scanf("%d", &m);
		//for (int i = 0; i <= 4; i++) {
			//for (int j = 0; j <= n; j++) cout << arr[i][j] << ' '; cout << endl;
		//}
		//for (int i = 0; i <= 4; i++) {
			//for (int j = 0; j <= n; j++) cout << sum[i][j] << ' '; cout << endl;
		//}
		printf("Case #%d:\n", cas);
		while (m--) {
			scanf("%d%d", &x, &y);
			x++, y++;
			int l = mn, r = mx, mid, mk, aim = y - x + 2 >> 1;
			while (l <= r) {
				mid = l + r >> 1;
				int c = count(x, y, mid, root);
				if (c >= aim) r = mid - 1, mk = mid;
				else l = mid + 1;
			}
			//cout << "mk " << mk << endl;
			printf("%I64d\n", getsum(x, y, mk, root));
		}
		puts("");
	}
	return 0;
}

