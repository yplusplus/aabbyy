#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1111;
const int INF = 0x77777777;
int q[2][N], qh[2], qt[2];
int n, g, tm[N], p[N], cur_time;
set<int> f[N];

void fix(int t) {
	int id;
	while (cur_time < t) {
		//cout << "cur_time " << cur_time << endl;
		cur_time++;
		bool ok = 1;
		for (int i = 0; i < 2; i++) {
			if (qh[i] < qt[i]) {
				ok = 0;
				//cout << "out " << id << endl;
				id = q[i][qh[i]++];
				tm[id] = cur_time;
				p[id] = i;
			}
		}
		if (ok) break;
	}
}

int pre_time(int x, int k) {
	int &h = qh[k], &t = qt[k], i = h;
	while (i < t) {
		if (f[x].find(q[k][i]) == f[x].end()) i++;
		else break;
	}
	if (i < t) i++;
	return i - h;
}

void insert(int x, int k) {
	int &h = qh[k], &t = qt[k], i = h;
	while (i < t) {
		if (f[x].find(q[k][i]) == f[x].end()) i++;
		else break;
	}
	if (i < t) i++;
	int j = t;
	while (j > i) q[k][j] = q[k][j - 1], j--;
	q[k][i] = x;
	t++;
}

void insert(int x) {
	int a = pre_time(x, 0), b = pre_time(x, 1);
	//cout << x << ' ' << a << ' ' << b << endl;
	insert(x, a >= b);
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	while (cin >> n >> g) {
		for (int i = 1; i <= n; i++) {
			int x;
			f[i].clear();
			while (cin >> x && x) f[i].insert(x);
		}
		memset(qh, 0, sizeof(qh));
		memset(qt, 0, sizeof(qt));
		cur_time = 1;
		for (int i = 1; i <= g; i++) {
			int t, k, x;
			cin >> t >> k;
			fix(t);
			cur_time = t;
			while (k--) {
				cin >> x;
				insert(x);
			}
		}
		fix(INF);
		for (int i = 1; i <= n; i++) cout << tm[i] << ' ' << (p[i] ? "right" : "left") << endl;
	}
	return 0;
}
