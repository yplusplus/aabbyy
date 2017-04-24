#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const LL MOD = 112233ll;
const int N = 33;
struct Mat {
	LL v[N][N];
	void init(LL val = 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) v[i][j] = 0;
			v[i][i] = val;
		}
	}
} ;

Mat operator * (Mat &a, Mat &b) {
	Mat ret;
	ret.init();
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			if (a.v[i][k]) {
				for (int j = 0; j < N; j++) ret.v[i][j] += a.v[i][k] * b.v[k][j] % MOD, ret.v[i][j] %= MOD;
			}
		}
	}
	return ret;
}

Mat operator ^ (Mat a, LL p) {
	Mat ret;
	ret.init(1);
	while (p > 0) {
		if (p & 1) ret = ret * a;
		a = a * a, p >>= 1;
	}
	return ret;
}

const int K = 6;
struct Node {
	Node *nx[K], *fail;
	bool end;
	void init() {
		for (int i = 0; i < K; i++) nx[i] = NULL;
		fail = 0, end = 0;
	}
} ;

Mat op;

struct Trie {
	Node node[N];
	int ttnode;
	Node *rt;
	void init() { rt = node + (ttnode = 0), node[ttnode++].init();}
	void insert(char *s) {
		Node *p = rt;
		while (*s) {
			int idx = *s - 'a';
			if (p->nx[idx] == NULL) p->nx[idx] = node + ttnode, node[ttnode++].init();
			p = p->nx[idx], s++;
		}
		p->end = true;
	}
	Node *q[N];
	void build() {
		int qh, qt;
		qh = qt = 0;
		for (int i = 0; i < K; i++) {
			if (rt->nx[i]) {
				rt->nx[i]->fail = rt;
				q[qt++] = rt->nx[i];
			}
		}
		while (qh < qt) {
			Node *p = q[qh++];
			for (int i = 0; i < K; i++) {
				if (p->nx[i]) {
					Node *t = p->fail;
					while (t != rt && t->nx[i] == NULL) t = t->fail;
					t = t->nx[i];
					if (t == NULL) t = rt;
					p->nx[i]->fail = t;
					q[qt++] = p->nx[i];
					if (t->end) p->nx[i]->end = true;
				}
			}
		}
		op.init();
		for (int i = 0; i < ttnode; i++) {
			for (int j = 0; j < K; j++) {
				if (node[i].end) continue;
				Node *t = node + i;
				while (t != rt && t->nx[j] == NULL) t = t->fail;
				t = t->nx[j];
				if (t == NULL) t = rt;
				if (t->end) continue;
				op.v[i][(int) (t - node)]++;
			}
		}
		//for (int i = 0; i < N; i++) {
			//cout << i << ": ";
			//for (int j = 0; j < N; j++) cout << op.v[i][j] << ' '; cout << endl;
		//}
	}
} trie;

int main() {
	char str[8][7] = { "aa", "bb", "cc", "dd", "ee", "ff", "abcdef", "fedcba"};
	trie.init();
	for (int i = 0; i < 8; i++) trie.insert(str[i]);
	trie.build();
	LL n;
	while (cin >> n) {
		if (n % 2 == 0) {
			cout << "0" << endl;
			continue;
		}
		Mat p = op, base;
		base.init();
		base.v[0][0] = 1;
		p = p ^ (n + 1 >> 1);
		base = base * p;
		LL ans = 0;
		for (int i = 0; i < N; i++) ans += base.v[0][i], ans %= MOD;
		//for (int i = 0; i < N; i++) {
			//for (int j = 0; j < N; j++) {
				//cout << base.v[i][j] << ' ';
			//}
			//cout << endl;
		//}
		cout << ans << endl;
	}
	return 0;
}




