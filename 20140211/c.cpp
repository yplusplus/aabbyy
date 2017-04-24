#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL K1 = 100003;
const LL K2 = 1600033;
const LL M1 = 15485863;
const LL M2 = 1000000007;
const LL OFFSET = 1ll << 31 | 1;
const int N = 1111;
const int M = 1111111;
LL ep1[N], ep2[N];
int n, m;
LL a[N << 1], b[M];
typedef pair<LL, LL> PLL;
#define x first
#define y second
map<PLL, int> pos;

void insert(PLL &a, const LL &x) {
	a.x = (a.x * K1 + x) % M1;
	a.y = (a.y * K2 + x) % M2;
}

void erase(PLL &a, const LL &x) {
	a.x -= ep1[n] * x % M1;
	if (a.x < 0) a.x += M1;
	a.y -= ep2[n] * x % M2;
	if (a.y < 0) a.y += M2;
}

void get_keys() {
	for (int i = 0; i < n; i++) a[i + n] = a[i];
	PLL cur(0, 0);
	int n2 = n << 1;
	pos.clear();
	for (int i = 0; i < n; i++) insert(cur, a[i]);
	for (int i = n; i < n2; i++) {
		pos[cur] = i - n;
		insert(cur, a[i]);
		erase(cur, a[i - n]);
	}
	//for (map<PLL, int>::iterator mi = pos.begin(); mi != pos.end(); mi++) cout << mi->x.x << ' ' << mi->x.y << ' ' << mi->y << endl;
}

int work() {
	PLL cur(0, 0);
	int ans = 0;
	for (int i = 0; i < n; i++) insert(cur, b[i]);
	for (int i = n; i <= m; i++) {
		//cout << cur.x << ' ' << cur.y << endl;
		if (pos.find(cur) != pos.end()) {
			int cnt = n, cp = pos[cur];
			//cout << "into " << cp << ' ' << i << endl;
			for (int j = i; j < m; j++, cnt++, cp++) {
				if (cp >= n) cp -= n;
				//cout << cp << ' ' << j << endl;
				if (a[cp] != b[j]) {
					i = j;
					break;
				}
				insert(cur, b[j]);
				erase(cur, b[j - n]);
			}
			ans = max(cnt, ans);
		}
		insert(cur, b[i]);
		erase(cur, b[i - n]);
	}
	return ans;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	for (int i = ep1[0] = 1; i < N; i++) ep1[i] = ep1[i - 1] * K1 % M1;
	for (int i = ep2[0] = 1; i < N; i++) ep2[i] = ep2[i - 1] * K2 % M2;
	while (cin >> n >> m) {
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < n; i++) a[i] += OFFSET;
		for (int i = 0; i < m; i++) cin >> b[i];
		for (int i = 0; i < m; i++) b[i] += OFFSET;
		get_keys();
		int ans = work();
		if (ans) cout << ans << endl;
		else cout << "bad" << endl;
	}
	return 0;
}
