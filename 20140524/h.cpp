#include <bits/stdc++.h>
using namespace std;

char digit[66];
const long long INF = 1LL << 62;
long long ma[2], mi[2];
long long ma_idx[2], mi_idx[2];
int n, k;

void check_max(long long t, int id) {
	if (t >= ma[0]) {
		ma[1] = ma[0];
		ma_idx[1] = ma_idx[0];
		ma[0] = t;
		ma_idx[0] = id;
	} else if (t >= ma[1]) {
		ma[1] = t;
		ma_idx[1] = id;
	}
}

void check_min(long long t, int id) {
	if (t <= mi[0]) {
		mi[1] = mi[0];
		mi_idx[1] = mi_idx[0];
		mi[0] = t;
		mi_idx[0] = id;
	} else if (t <= ma[1]) {
		mi[1] = t;
		mi_idx[1] = id;
	}
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		ma[0] = ma[1] = -INF;
		mi[0] = mi[1] = INF;
		for (int i = 0; i < n; i++) {
			scanf("%s", digit);
			long long t = 0;
			for (int j = 0; j < k; j++) {
				t = t * 2 + digit[j] - '0';
			}
			check_max(t, i);
			check_min(t, i);
			for (int j = 0; j < k; j++) {
				digit[j] = 1 - (digit[j] - '0') + '0';
			}
			t = 0;
			for (int j = 0; j < k; j++) {
				t = t * 2 + digit[j] - '0';
			}
			check_max(t, i);
			check_min(t, i);
		}
		cout << "Case #" << Case++ << ": ";
		if (n == 1) {
			cout << 0 << endl;
		} else {
			long long ans = -INF;
			if (ma_idx[0] != mi_idx[0]) ans = max(ans, ma[0] - mi[0]);
			if (ma_idx[0] != mi_idx[1]) ans = max(ans, ma[0] - mi[1]);
			if (ma_idx[1] != mi_idx[0]) ans = max(ans, ma[1] - mi[0]);
			if (ma_idx[1] != mi_idx[1]) ans = max(ans, ma[1] - mi[1]);
			cout << ans << endl;
		}
	}
	return 0;
}
