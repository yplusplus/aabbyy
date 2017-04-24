#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
const pll KEY = pll(20023, 104729);
const pll MOD = pll(1870667, 15485863);
const int N = 4444;
int n;
char str[N];
pll fac[N];
#define x first
#define y second

pll operator% (const pll &a, const pll &b) { return pll(a.x % b.x, a.y % b.y); }
pll operator+ (const pll &a, const pll &b) { return pll(a.x + b.x, a.y + b.y) % MOD; }
pll operator- (const pll &a, const pll &b) { return (pll(a.x - b.x, a.y - b.y) + MOD) % MOD; }
pll operator* (const pll &a, const pll &b) { return pll(a.x * b.x, a.y * b.y); }
pll operator* (const pll &a, int b) { return pll(a.x * b, a.y * b) % MOD; }

int pre[256];

struct Node {
	pair<int, int> val;
	int st;
	Node() {}
	Node(pair<int, int> val, int st) : val(val), st(st) {}
	bool operator<(const Node &x) const { return val < x.val; }
	bool operator==(const Node &x) const { return val == x.val; }
};// vec[4010][4010];

vector<Node> vec[4444];

void solve() {
	int len = strlen(str);
	int cnt[N];
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i <= len; ++i) vec[i].resize(len - i + 1);
	for (int i = 0; i < len; i++) {
		memset(pre, -1, sizeof(pre));
		pll val(0, 0);
		for (int j = i; j < len; j++) {
			char ch = str[j];
			if (pre[ch] != -1) val = (val + fac[j - i] * (j - pre[ch])) % MOD;
			vec[j - i + 1][cnt[j - i + 1]++] = Node(make_pair(val.x, val.y), i);
			pre[ch] = j;
		}
	}
	int ans = 0;
	int l = -1, st = -1;
	for (int i = 1; i <= len; i++) {
		if (i * (len - i + 1) <= ans) continue;
		sort(vec[i].begin(), vec[i].end());
		//sort(vec[i], vec[i] + cnt[i]);
		for (int j = 0; j < vec[i].size(); j++) {
		//for (int j = 0; j < cnt[i]; j++) {
			int k = j;
			//while (k + 1 < vec[i].size() && vec[i][k + 1] == vec[i][j]) k++;
			while (k + 1 < cnt[i] && vec[i][k + 1] == vec[i][j]) k++;
			int tmp = (k - j + 1) * i;
			if (tmp > ans) {
				ans = tmp;
				l = i;
				st = vec[i][j].st;
			}
			j = k;
		}
	}
	for (int i = 0; i < l; i++) {
		putchar(str[i + st]);
	}
	puts("");
}

int main() {
	fac[0] = pll(1, 1);
	for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * KEY % MOD;
	freopen("pattern.in", "r", stdin);
	freopen("pattern.out", "w", stdout);
	//memset(str, 'a', sizeof(str)); str[4000] = 0;
	scanf("%s", str);
	solve();
	return 0;
}
