#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1111;
const int INF = 0x77777777;
int maze[N][N];
int n, s, t;
typedef pair<int, int> PII;
#define x first
#define y second
PII q[N * N << 1];

bool bfs() {
	int qh, qt, L, R;
	qh = qt = 0;
	q[qt++] = PII(-s, 0);
	int p, h, ap;
	while (qh < qt) {
		p = q[qh].x; h = q[qh].y; ap = abs(p);
		//cout << p << ' ' << h << endl;
		qh++;
		L = R = INF;
		if (ap > 1) {
			L = upper_bound(maze[ap - 1] + 1, maze[ap - 1] + maze[ap - 1][0] + 1, h) - maze[ap - 1];
			if (L > maze[ap - 1][0]) L = INF;
			else L = maze[ap - 1][L];
		}
		if (ap < n) {
			R = upper_bound(maze[ap] + 1, maze[ap] + maze[ap][0] + 1, h) - maze[ap];
			if (R > maze[ap][0]) R = INF;
			else R = maze[ap][R];
		}
		if (p < 0) {
			if (L == INF && R == INF) {
				if (ap == t) return 1;
			} else {
				q[qt++] = PII(ap, min(L, R));
				if (L == INF) q[qt++] = PII(p - 1, R);
				else if (R == INF) q[qt++] = PII(p + 1, L);
				else {
					if (L < R) q[qt++] = PII(p + 1, L);
					else q[qt++] = PII(p - 1, R);
				}
			}
		} else {
			if (L == INF && R == INF) {
				if (ap == t) return 1;
			} else if (L == INF) q[qt++] = PII(p + 1, R);
			else if (R == INF) q[qt++] = PII(p - 1, L);
			else {
				if (L < R) q[qt++] = PII(p - 1, L);
				else q[qt++] = PII(p + 1, R);
			}
		}
	}
	return 0;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i < n; i++) {
			scanf("%d", maze[i]);
			for (int j = 1; j <= maze[i][0]; j++) scanf("%d", maze[i] + j);
			sort(maze[i] + 1, maze[i] + maze[i][0] + 1);
		}
		scanf("%d%d", &s, &t);
		if (bfs()) puts("Yes");
		else puts("No");
	}
	return 0;
}
