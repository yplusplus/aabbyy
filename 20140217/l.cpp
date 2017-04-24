#include <bits/stdc++.h>
using namespace std;

const int N = 155555;
const int K = 26;
typedef long long LL;
typedef pair<LL, LL> PLL;
#define x first
#define y second
PLL ep1[N], ep2[N];
const PLL K1(100003, 200003);
const PLL K2(400009, 1600033);
const PLL MOD(6400013, 1000000007);

PLL operator + (const PLL &a, const PLL &b) { return PLL(a.x + b.x, a.y + b.y); }
PLL operator * (const PLL &a, const PLL &b) { return PLL(a.x * b.x, a.y * b.y); }
PLL operator % (const PLL &a, const PLL &b) { return PLL(a.x % b.x, a.y % b.y); }

struct Node {
	Node *nx[K];
	bool end;
	void init() {
		memset(nx, 0, sizeof nx);
		end = 0;
	}
} node[N];

struct Trie {
	int ttnode;
	Node *rt;
	Node *mem(bool a = 0) {
		node[ttnode].init();
		return node + ttnode++;
	}
	void init() {
		ttnode = 0;
		rt = mem();
	}
	void insert(char *s) {
		Node *p = rt;
		int idx;
		while (*s) {
			idx = *s - 'a';
			if (p->nx[idx] == 0) p->nx[idx] = mem();
			p = p->nx[idx];
			s++;
		}
		p->end = 1;
	}
	PLL ans[N];
	int tt;
	PLL dfs(const Node *const p) {
		PLL sum(0, 0), tmp;
		for (int i = 0; i < K; i++) {
			if (p->nx[i]) tmp = dfs(p->nx[i]);
			else tmp = PLL(0, 0);
			tmp = tmp * K1 % MOD;
			sum = (sum * K2 + tmp) % MOD;
		}
		sum = (sum * PLL(3, 3) + PLL(p->end + 1, p->end + 1)) % MOD;
		//cout << sum.x << ' ' << sum.y << endl;
		return ans[tt++] = sum;
	}
	int cal() { 
		tt = 0;
		dfs(rt);
		sort(ans, ans + tt);
		return unique(ans, ans + tt) - ans;
	}
} trie;

int main() {
	ios::sync_with_stdio(0);
	int n;
	char buf[33];
	ep1[0] = ep2[0] = PLL(1, 1);
	for (int i = 1; i < N; i++) ep1[i] = ep1[i - 1] * MOD;
	for (int i = 1; i < N; i++) ep2[i] = ep2[i - 1] * MOD; 
	while (cin >> n) {
		trie.init();
		while (n--) {
			cin >> buf;
			trie.insert(buf);
		}
		cout << trie.cal() << endl;
	}
	return 0;
}
