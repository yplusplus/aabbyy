#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 18;
const int M = 30;
const int K = 2;
typedef long long LL;

struct Node {
	Node *nx[K];
	int cnt;
	void init() {
		nx[0] = nx[1] = 0;
		cnt = 0;
	}
} node[N * M];
int ttNode;

void init() { ttNode = 0; }
Node *mem() {
	node[ttNode].init();
	return node + ttNode++;
}

struct Trie {
	Node *rt;
	void init() {
		::init();
		rt = ::mem();
	}
	void insert(int x) {
		Node *p = rt;
		int idx;
		for (int i = M - 1; i >= 0; --i) {
			idx = (x & 1 << i) != 0;
			if (!p->nx[idx]) p->nx[idx] = mem();
			++p->cnt;
			p = p->nx[idx];
		}
		++p->cnt;
	}
	int find(int m, int cur, int pos, Node const *p) {
		if (pos < 0) return cur <= m ? p->cnt : 0;
		if ((cur & ~((1LL << pos + 1) - 1)) > m) return 0;
		if ((cur | (1LL << pos + 1) - 1) <= m) return p->cnt;
		int sum = 0;
		if (p->nx[0]) sum += find(m, cur, pos - 1, p->nx[0]);
		if (p->nx[1]) sum += find(m, cur ^ (1 << pos), pos - 1, p->nx[1]);
		return sum;
	}
	int find(int x, int m) { return find(m, x, M - 1, rt); }
} trie;

int run() {
	int _, n, m, x, cur;
	cin >> _;
	while (_--) {
		cin >> n >> m;
		trie.init();
		trie.insert(0);
		cur = 0;
		LL ans = 0;
		for (int i = 0; i < n; ++i) {
			cin >> x;
			cur ^= x;
			//cout << "find" << endl;
			ans += trie.find(cur, m);
			//cout << "cur " << cur << ' ' << ans << endl;
			//cout << "find end" << ' ' << ans << endl;
			trie.insert(cur);
		}
		cout << ans << endl;
	}
	return 0;
}

int main() {
	//freopen("in_a", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
