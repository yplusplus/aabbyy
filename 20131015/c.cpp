#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int n, m, k;
const int N = 111;
int c[N][N];
typedef pair<int, int> PII;
#define x first
#define y second
PII id[N][N];
int a1[N * N], a2[N * N];

int main() {
	ios::sync_with_stdio(0);
	while (cin >> n >> k >> m) {
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; i++) {
			int g = i % k + 1;
			cout << g << endl;
			c[g][++c[g][0]] = i;
		}
		int t = 0, d = n + 1 >> 1;
		set<PII> used;
		for (int i = 0; i < d && t < m; i++) {
			int g1 = i << 1 | 1, g2 = i + 1 << 1;
			if (g2 > n) {
				g2 = 1;
				if (g1 % k == g2 % k) g2 = 2;
			}
			if (g1 % k > g2 % k) swap(g1, g2);
			a1[t] = g1;
			a2[t] = g2;
			used.insert(PII(a1[t], a2[t]));
			t++;
		}
		for (int i = 1; i <= k && t < m; i++) {
			for (int ii = 1; ii <= c[i][0] && t < m; ii++) {
				for (int j = i + 1; j <= k && t < m; j++) {
					for (int jj = 1; jj <= c[j][0] && t < m; jj++) {
						if (used.find(PII(c[i][ii], c[j][jj])) != used.end()) continue;
						a1[t] = c[i][ii], a2[t] = c[j][jj];
						t++;
					}
				}
			}
		}
		//cout << t << endl;
		for (int i = 0; i < t; i++) cout << a1[i] << ' ' << a2[i] << endl;
	}
	return 0;
}



