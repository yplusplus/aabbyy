#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
const int N = 55;
double x[N], y[N];
double g[N][N];
bool visit[N];
double att[N];
int n;
int m[N];
double dist[N];

bool equal(double a, double b) {
	return fabs(a - b) < eps;
}

double sq(double x) {
	return x * x;
}

double get_gance(int a, int b) {
	return sqrt(sq(x[a] - x[b]) + sq(y[a] - y[b]));
}

void prim(int s) {
	for (int i = 0; i < n; i++) {
		visit[i] = false;
		att[i] = 1e10;
	}
	att[s] = 0;
	while (true) {
		int u = -1;
		for (int i = 0; i < n; i++) {
			if (!visit[i] && (u == -1 || att[u] > att[i])) u = i;
		}
		if (u == -1) break;
		visit[u] = true;
		for (int i = 0; i < n; i++) {
			if (!visit[i]) {
				att[i] = min(att[i], g[u][i]);
			}
		}
	}
}

int cnt[N];
void dij(int s) {
	for (int i = 0; i < n; i++) {
		cnt[i] = 0;
		visit[i] = false;
		dist[i] = 1e10;
	}
	dist[s] = 0;
	while (true) {
		int u = -1;
		for (int i = 0; i < n; i++) {
			if (!visit[i] && (u == -1 || dist[u] > dist[i])) u = i;
		}
		if (u == -1) break;
		visit[u] = true;
		for (int i = 0; i < n; i++) {
			//if (!visit[i] ) {
			if (!visit[i] && equal(g[u][i], att[i])) {
				//cnt[i] ++;
				dist[i] = min(dist[i], max(dist[u], g[u][i]));
				//dist[i] = min(dist[i], dist[u] + g[u][i]);
				//att[i] = min(att[i], g[u][i]);
			}
		}
	}
	//for (int i = 0; i < n; i++) { cout << cnt[i] << " "; } cout << endl;
}


void solve(int Case) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g[i][j] = get_gance(i, j);
			//cout << g[i][j] << " ";
		}
		//cout << endl;
	}
	prim(0);
	//for (int i = 0; i < n; i++) { cout << att[i] << " "; } cout << endl;
	dij(0);
	double ans = 0;
	double sum = 0;
	for (int i = 0; i < n; i++) {
		ans += dist[i] * m[i];
		sum += m[i];
	}
	ans /= sum;
	printf("Island Group: %d Average %.2f\n", Case, ans);
}

int main() {
	int Case = 1;
	while (~scanf("%d", &n), n) {
		for (int i = 0; i < n; i++) { scanf("%lf%lf%d", &x[i], &y[i], &m[i]); }
		solve(Case++);
		puts("");
	}
	return 0;
}
