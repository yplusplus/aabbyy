#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

char *ptr;
int get_num() {
	int x = 0;
	while (isdigit(*ptr)) {
		x = x * 10 + *ptr - '0';
		++ptr;
	}
	return x;
}

string get_elem() {
	string x;
	x += *ptr; ++ptr;
	while (islower(*ptr)) {
		x += *ptr;
		++ptr;
	}
	return x;
}

typedef long long LL;
typedef map<string, int> MSI;
MSI id;
int find(const string &s) {
	if (id.find(s) == id.end()) id[s] = id.size() - 1;
	return id[s];
}

const int N = 33;
LL mat[N][N];

void show_mat(int n, int m) {
	cerr << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cerr << mat[i][j] << ' ';
		cerr << endl;
	}
}

MSI merge(MSI a, MSI b) {
	MSI c;
	for (MSI::iterator mi = a.begin(); mi != a.end(); ++mi) c[mi->x] += mi->y;
	for (MSI::iterator mi = b.begin(); mi != b.end(); ++mi) c[mi->x] += mi->y;
	return c;
}

MSI multi(MSI a, int p) {
	MSI c;
	for (MSI::iterator mi = a.begin(); mi != a.end(); mi++) c[mi->x] += mi->y * p;
	return c;
}

MSI rec;
MSI dfs() {
	MSI cnt;
	if (0 == *ptr) return cnt;
	while (*ptr) {
		if (')' == *ptr) break;
		if ('(' == *ptr) {
			++ptr;
			MSI tmp = dfs();
			if (isdigit(*ptr)) cnt = merge(cnt, multi(tmp, get_num()));
			else cnt = merge(cnt, tmp);
		} else {
			string e = get_elem();
			if (isdigit(*ptr)) cnt[e] += get_num();
			else ++cnt[e];
		}
	}
	++ptr;
	return cnt;
}

MSI get_all(const string &s) {
	rec.clear();
	ptr = const_cast<char *>(s.c_str());
	return dfs();
}

void add(const string &a, int col, int val) {
	MSI elem = get_all(a);
	//cerr << a << "   ";
	for (MSI::iterator mi = elem.begin(); mi != elem.end(); mi++) {
		//cerr << mi->x << ':' << mi->y << ' ';
		int row = find(mi->x);
		mat[row][col] = mi->y * val;
	}
	//cerr << endl;
}

typedef pair<LL, LL> Factor;
inline Factor fix(const Factor &a) {
	LL g = __gcd(abs(a.x), abs(a.y));
	if (a.y < 0) return Factor(-a.x / g, -a.y / g);
	return Factor(a.x / g, a.y / g);
}
Factor operator + (const Factor &a, const Factor &b) { return fix(Factor(a.x * b.y + a.y * b.x, a.y * b.y)); }
Factor operator - (const Factor &a, const Factor &b) { return fix(Factor(a.x * b.y - a.y * b.x, a.y * b.y)); }
Factor operator * (const Factor &a, const Factor &b) { return fix(Factor(a.x * b.x, a.y * b.y)); }
Factor operator / (const Factor &a, const Factor &b) { return fix(Factor(a.x * b.y, a.y * b.x)); }
Factor operator + (const Factor &a, const LL &b) { return fix(Factor(a.x + b * a.y, a.y)); }
Factor operator - (const Factor &a, const LL &b) { return fix(Factor(a.x - b * a.y, a.y)); }
Factor operator * (const Factor &a, const LL &b) { return fix(Factor(a.x * b, a.y)); }
Factor operator / (const Factor &a, const LL &b) { return fix(Factor(a.x, a.y * b)); }

Factor ans[N];
bool vis[N];
int check(int x, int m) {
	int mk = -1;
	for (int i = 0; i < m; i++) {
		if (vis[i]) continue;
		if (!mat[x][i]) continue;
		if (~mk) return -1;
		else mk = i;
	}
	return mk;
}

template<class T> inline T lcm(const T &a, const T &b) { return a / __gcd(a, b) * b; }
bool work(int n, int m) {
	for (int p = 0; p < m; p++) {
		for (int i = p + 1; i < n; i++) {
			while (mat[i][p]) {
				LL k = mat[p][p] / mat[i][p];
				for (int j = p; j < m; j++) {
					mat[p][j] = mat[p][j] - mat[i][j] * k;
					swap(mat[p][j], mat[i][j]);
				}
			}
		}
	}
	memset(ans, 0, sizeof ans);
	memset(vis, 0, sizeof vis);
	ans[m - 1] = Factor(1, 1);
	vis[m - 1] = 1;
	while (1) {
		bool ok = 1;
		for (int i = 0; ok && i < n; i++) {
			int id = check(i, m);
			Factor sum(0, 1);
			if (~id) {
				for (int j = 0; j < m; j++) if (vis[j]) sum = sum - ans[j] * mat[i][j];
				ans[id] = sum / mat[i][id];
				vis[id] = 1;
				ok = 0;
			}
		}
		if (ok) {
			bool ok = 1;
			for (int i = m - 1; i >= 0; i--) {
				if (!vis[i]) {
					ans[i] = Factor(1, 1);
					vis[i] = 1;
					ok = 0;
				}
			}
			if (ok) break;
		}
	}
	int max_row = n - 1;
	while (max_row) {
		bool ok = 0;
		for (int i = 0; !ok && i < m; ++i) if (mat[max_row][i]) ok = 1;
		if (ok) break;
		--max_row;
	}
	if (m - max_row >= 3) return 0;
	//show_mat(n, m);
	//for (int i = 0; i < m; i++) cerr << i << " ~~~~~ " << ans[i].x << ' ' << ans[i].y << ' ' << vis[i] << endl;
	LL l = 1;
	for (int i = 0; i < m; i++) {
		if (ans[i].x <= 0) return 0;
		l = lcm(ans[i].y, l);
	}
	for (int i = 0; i < n; i++) {
		Factor sum(0, 1);
		for (int j = 0; j < m; j++) sum = sum + ans[j] * mat[i][j];
		if (sum.x != 0) return 0;
	}
	//cerr << l << endl;
	LL g = ans[0].x * (l / ans[0].y);
	for (int i = 0; i < m; i++) g = __gcd(ans[i].x * (l / ans[i].y), g);
	for (int i = 0; i < m; i++) cout << ' ' << ans[i].x * (l / ans[i].y) / g;
	cout << endl;
	return 1;
}

int main() {
	//freopen("in", "r", stdin);
	int n, m, cas = 0;
	while (cin >> n >> m && n + m) {
		string product;
		id.clear();
		memset(mat, 0, sizeof mat);
		for (int i = 0; i < n; i++) {
			cin >> product;
			add(product, i, 1);
		}
		for (int i = 0; i < m; i++) {
			cin >> product;
			add(product, i + n, -1);
		}
		//show_mat(id.size(), n + m);
		cout << "Case " << ++cas << ":";
		if (!work(id.size(), n + m)) cout << " No" << endl;
	}
	return 0;
}
