#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 22;
int n, m;
int target[N];
int a[N][N];
int cnt[1 << 17];
bool check(int tmp[]) {
	for (int i = 0; i < n; i++) {
		if (tmp[i] < target[i]) return false;
	}
	return true;
}

int cmp(int a, int b) {
	for (int i = 0; i < n; i++) {
		int aa = a >> i & 1;
		int bb = b>> i & 1;
		if (aa > bb) return -1;
		else if (aa < bb) return 1;
	}
	return 0;
}

int main() {
	cnt[0] = 0;
	for (int i = 1; i < 1 << 17; i++) {
		cnt[i] = cnt[i >> 1] + (i & 1);
	}
	ios::sync_with_stdio(false);
	while (cin >> n) {
		for (int i = 0; i < n; i++) cin >> target[i];
		cin >> m;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a[i][j];
			}
		}
		int ans = 0;
		int tmp[N];
		for (int mask = 0; mask < (1 << m); mask++) {
			memset(tmp, 0, sizeof(tmp));
			for (int i = 0; i < m; i++) {
				if (mask >> i & 1) {
					for (int j = 0; j < n; j++) {
						tmp[j] += a[i][j];
					}
				}
			}
			if (!check(tmp)) continue;
			if (cnt[mask] > cnt[ans] || (cnt[mask] == cnt[ans] && cmp(ans, mask) == 1)) ans = mask;
		}
		cout << cnt[ans];
		//cout << ans << endl;
		for (int i = 0; i < m; i++) {
			if (ans >> i & 1) cout << " " << i + 1;
		}
		cout << endl;
	}
	return 0;
}

