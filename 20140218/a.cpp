#include <bits/stdc++.h>
using namespace std;

typedef double DB;
const int N = 6;
const int K = 3;
const DB FINF = 1e100;
const DB PI = acos(-1.0);
DB x[N][K], box[2][K], r[N];
template<class T> inline T sqr(T x) { return x * x; }

DB cal(const int *const a, int n) {
	for (int i = 0; i < n; i++) {
		r[i] = FINF;
		for (int j = 0; j < i; j++) {
			DB s = 0;
			for (int k = 0; k < K; k++) s += sqr(x[a[i]][k] - x[a[j]][k]);
			r[i] = min(max(sqrt(s) - r[j], 0.0), r[i]);
		}
		for (int j = 0; j < 2; j++) for (int k = 0; k < K; k++) r[i] = min(fabs(box[j][k] - x[a[i]][k]), r[i]);
	}
	DB sum = 1;
	for (int i = 0; i < K; i++) sum *= fabs(box[0][i] - box[1][i]);
	for (int i = 0; i < n; i++) sum -= 4 * r[i] * r[i] * r[i] * PI / 3;
	return sum;
}

bool check(int a) {
	for (int i = 0; i < K; i++) if (box[0][i] > x[a][i] || x[a][i] > box[1][i]) return 0;
	return 1;
}

int main() {
	int n, cas = 1;
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(0);
	while (cin >> n && n) {
		int tt = 0;
		for (int i = 0; i < 2; i++) for (int j = 0; j < K; j++) cin >> box[i][j];
		for (int i = 0; i < K; i++) if (box[0][i] > box[1][i]) swap(box[0][i], box[1][i]);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < K; j++) cin >> x[tt][j];
			if (check(tt)) tt++;
		}
		n = tt;
		//cout << n << endl;
		int a[N];
		DB ans = FINF;
		for (int i = 0; i < n; i++) a[i] = i;
		do {
			ans = min(cal(a, n), ans);
		} while (next_permutation(a, a + n));
		cout << "Box " << cas++ << ": " << ans << endl << endl;
	}
	return 0;
}
