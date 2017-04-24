#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
#define ll long long
const int N = 11111;
int n;
ll a[N];
struct BIT {
	ll c[N];
	void clear() { memset(c, 0, sizeof(c)); }
	void update(int l, int r, int v) {
		update(l, v);
		update(r + 1, -v);
	}
	void update(int x, int v) {
		for (int i = x; i < N; i += lowbit(i)) c[i] += v;
	}
	int query(int x) {
		if (x == 0) return 0;
		int res = 0;
		for (int i = x; i; i -= lowbit(i)) res += c[i];
		return res;
	}
	int lowbit(int x) { return x & (-x); }
} bit;

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		bit.clear();
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			bit.update(i, i, a[i]);
			//cout << bit.query(i) << endl;
		}
		//cout << 123 << endl;
		a[0] = a[n + 1] = 0;
		int pos = 0;
		int ans = n + 1;
		for (int i = 1; i <= n + 1; i++) {
			int pre = bit.query(i - 1);
			//cout << i << " " << pre << " " << a[i] << endl;
			if (a[i] < pre) {
				int delta = pre - a[i];
				//cout << "delta = " << delta << endl;
				if (pos == 0) pos++;
				bit.update(pos, i - 1, -delta);
				while (bit.query(pos) < 0) {
					//cout << pos << " " << bit.query(pos) << endl;
					pos++;
				}
				//cout << i << " " << pos << endl;
				ans = min(ans, i - pos);
			}
		}
		cout << ans << endl;
	}
	return 0;
}

