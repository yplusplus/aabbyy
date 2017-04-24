#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
const pll KEY = pll(20023, 104729);
const pll MOD = pll(1870667, 15485863);
const int N = 222;
const int M = N * 50 * 50 / 2;
int n;
char str[N][55];
set<pll> state;
map<pll, int> dp;
map<pll, int> id;
pll fac[N];
int alloc;
bool e[M];
bool start[256];
vector<pll> vec[M];
#define x first
#define y second

pll operator% (const pll &a, const pll &b) { return pll(a.x % b.x, a.y % b.y); }
pll operator+ (const pll &a, const pll &b) { return pll(a.x + b.x, a.y + b.y) % MOD; }
pll operator- (const pll &a, const pll &b) { return (pll(a.x - b.x, a.y - b.y) + MOD) % MOD; }
pll operator* (const pll &a, const pll &b) { return pll(a.x * b.x, a.y * b.y); }
pll operator* (const pll &a, int b) { return pll(a.x * b, a.y * b) % MOD; }

pll sum[55];
void insert(char *str) {
	int len = strlen(str + 1);
	for (int i = 1; i <= len; i++) {
		pll val = pll(0, 0), tmp;
		start[str[i]] = true;
		for (int j = i; j <= len; j++) {
			val = (val + fac[j - i] * (str[j])) % MOD;
			state.insert(val);
			if (id.count(val) == 0) { id[val] = alloc++; }
			int u = id[val];
			if (i > 1) {
				tmp = (fac[0] * str[i - 1] + val * KEY) % MOD;
				vec[u].push_back(tmp);
			}
			if (j < len) {
				tmp = (val + fac[j - i + 1] * str[j + 1]);
				vec[u].push_back(tmp);
			}
			if (i == 1 && j == len) { e[u] = true; }
		}
	}
}

int dfs(pll val, int len) {
	int u = id[val];
	if (e[u]) return 1;
	if (dp.count(val)) { return dp[val]; }
	for (int i = 0; i < vec[u].size(); i++) {
		pll tmp = vec[u][i];
		if (!dfs(tmp, len + 1)) { return dp[val] = 1; }
	}
	return dp[val] = 0;
}

void solve() {
	alloc = 0;
	memset(start, false, sizeof(start));
	memset(e, false, sizeof(e));
	for (int i = 0; i < n; i++) { insert(str[i]); }
	string ans_str;
	for (int i = 33; i <= 126; i++) {
		if (start[i] && !dfs(pll(i, i), 1)) {
			ans_str += char(i);
		}
	}
	if (ans_str.length() > 0) {
		puts("First");
		puts(ans_str.c_str());
	} else {
		puts("Second");
	}
}

int main() {
	fac[0] = pll(1, 1);
	for (int i = 1; i < N; i++) { fac[i] = (fac[i - 1] * KEY) % MOD; }
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) { scanf("%s", str[i] + 1); }
	solve();
	return 0;
}
