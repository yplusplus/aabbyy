#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 11111;
PII rec[N];
int x[N];
bool cmp(PII a, PII b) { return a.second > b.second;}

int main() {
	//freopen("in", "r", stdin);
	int T, n;
	scanf("%d", &T);
	while (T--) {
		LL s, p;
		s = 0;
		cin >> p >> n;
		for (int i = 0; i < n; i++) {
			scanf("%d", x + i);
			rec[i] = PII(x[i], -i);
			s += x[i];
		}
		if (s >= p) {
			LL t = p;
			sort(rec, rec + n);
			int i = 0;
			LL cur = 0;
			while (i < n && t > 0) {
				while (rec[i].first <= cur) i++;
				if (t <= n - i) break;
				LL d = rec[i].first - cur;
				if (d * (n - i) <= t) {
					t -= d * (n - i);
					cur = rec[i].first;
				} else {
					LL a = t / (n - i);
					t -= a * (n - i);
					cur += a;
				}
			}
			for (int j = 0; j < n; j++) rec[j].first = max(rec[j].first - cur, 0ll);
			i = n - 1;
			while (t-- && i >= 0) rec[i].first--, i--;
			t = 0;
			sort(rec, rec + n, cmp);
			for (int j = 0; j < n; j++) {
				t += x[j] - rec[j].first;
				if (j) putchar(' ');
				printf("%d", x[j] - rec[j].first);
			}
			if (t != p) while (1);
			puts("");
		} else puts("IMPOSSIBLE");
	}
	return 0;
}