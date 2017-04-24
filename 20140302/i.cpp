#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
typedef vector<PII> VP;
#define x first
#define y second

const int N = 333333;
struct Node {
	int x, st, gcd[2], cnt[2], sz;
	Node *c[2], *p;
	void init(int a, int b) {
		c[0] = c[1] = p = 0;
		x = a, st = b;
		if (-1 == b) gcd[0] = gcd[1] = cnt[0] = cnt[1] = sz = 0;
		else {
			gcd[b] = a, gcd[b ^ 1] = 0;
			cnt[b] = sz = 1, cnt[b ^ 1] = 0;
		}
	}
} node[N];

int ttnode;
stack<Node *> trash;

void init() {
	ttnode = 0;
	while (!trash.empty()) trash.pop();
}

Node *mem(int a, int b) {
	Node *t;
	if (trash.empty()) t = node + ttnode++;
	else t = trash.top(), trash.pop();
	t->init(a, b);
	return t;
}

void recycle(Node *&x) {
	trash.push(x);
	x = 0;
}

struct SPT {
	Node *root, *null, *head, *tail;
	void build(const VP &rec, int n) {
		null = mem(0, -1); // null pointer
		build(rec, 0, n - 1, root); // recurse build tree
		root->p = null;
		head = tail = root;
		while (head->c[0] != null) ++head->sz, head = head->c[0]; // add tail
		++head->sz;
		head->c[0] = mem(0, 0);
		head->c[0]->p = head;
		head = head->c[0];
		--head->cnt[0];
		head->c[0] = head->c[1] = null;
		while (tail->c[1] != null) ++tail->sz, tail = tail->c[1]; // add head
		++tail->sz;
		tail->c[1] = mem(0, 0);
		tail->c[1]->p = tail;
		tail = tail->c[1];
		--tail->cnt[0];
		tail->c[0] = tail->c[1] = null;
		//cout << null << ' ' << head << ' ' << tail << ' ' << root << endl;
	}
	void build(const VP &rec, int l, int r, Node *&rt) {
		if (l > r) {
			rt = null;
			return ;
		}
		int m = l + r >> 1;
		rt = mem(rec[m].x, rec[m].y);
		build(rec, l, m - 1, rt->c[0]);
		if (rt->c[0] != null) rt->c[0]->p = rt;
		build(rec, m + 1, r, rt->c[1]);
		if (rt->c[1] != null) rt->c[1]->p = rt;
		up(rt);
	}
	void up(Node *rt) {
		rt->sz = rt->c[0]->sz + rt->c[1]->sz + 1;
		if (rt == head || rt == tail) return ;
		rt->cnt[0] = rt->c[0]->cnt[0] + rt->c[1]->cnt[0];
		rt->cnt[1] = rt->c[0]->cnt[1] + rt->c[1]->cnt[1];
		++rt->cnt[rt->st];
		rt->gcd[0] = __gcd(rt->c[0]->gcd[0], rt->c[1]->gcd[0]);
		rt->gcd[1] = __gcd(rt->c[0]->gcd[1], rt->c[1]->gcd[1]);
		rt->gcd[rt->st] = __gcd(rt->x, rt->gcd[rt->st]);
	}
	void rotate(Node *x, bool r) {
		Node *y = x->p;
		bool l = !r;
		y->c[l] = x->c[r];
		if (x->c[r] != null) x->c[r]->p = y;
		x->p = y->p;
		if (y->p != null) y->p->c[y->p->c[1] == y] = x;
		x->c[r] = y;
		y->p = x;
		if (y == root) root = x;
		up(y);
	}
	void splay(Node *x, Node *p) {
		while (x->p != p) {
			if (x->p->p == p) rotate(x, x->p->c[0] == x);
			else {
				Node *y = x->p, *z = y->p;
				if (z->c[0] == y) {
					if (y->c[0] == x) rotate(y, 1);
					else rotate(x, 0);
					rotate(x, 1);
				} else {
					if (y->c[0] == x) rotate(x, 1);
					else rotate(y, 0);
					rotate(x, 0);
				}
			}
		}
		up(x);
	}
	Node *get_pos(int k) {
		Node *p = root;
		int lc;
		while (1) {
			lc = p->c[0] ? p->c[0]->sz : 0;
			if (k == lc + 1) break;
			else if (k <= lc) p = p->c[0];
			else k -= lc + 1, p = p->c[1];
		}
		return p;
	}
	void insert(const PII &a, int p) {
		Node *pl = get_pos(p + 1), *pr = get_pos(p + 2);
		Node *tmp = mem(a.x, a.y);
		//pre();
		splay(pl, null); splay(pr, pl);
		//cout << "insert " << pl << ' ' << pr << ' ' << pl->c[0] << ' ' << root << endl;
		//cout << pl->c[1] << ' ' << pr->c[0] << ' ' << pr->c[1] << endl;
		pr->c[0] = tmp, tmp->p = pr;
		tmp->c[0] = tmp->c[1] = null;
		//cout << tmp->sz << endl;
		splay(tmp, null);
	}
	Node *get_seg(int l, int r) {
		Node *pl = get_pos(l), *pr = get_pos(r + 2);
		//cout << "get_seg " << pl << ' ' << pr << endl;
		splay(pl, null); splay(pr, pl);
		return pr->c[0];
	}
	void erase(int p) {
		Node *s = get_seg(p, p);
		s->p->c[0] = null;
		splay(s->p, null);
		recycle(s);
	}
	int get_gcd(int l, int r, int st) {
		Node *tmp = get_seg(l, r);
		if (tmp->cnt[st]) return tmp->gcd[st];
		return -1;
	}
	void change(int p) {
		++p;
		Node *tmp = get_pos(p);
		tmp->st = !tmp->st;
		splay(tmp, null);
	}
	void modify(int x, int p) {
		++p;
		Node *tmp = get_pos(p);
		tmp->x = x;
		splay(tmp, null);
	}
	void pre() { pre(root); cout << endl; }
	void pre(Node *rt) {
		if (rt == null) return ;
		//cout << rt << ' ' << rt->x << ' ' << rt->sz << ' ' << rt->c[0] << ' ' << rt->c[1] << ' ' << rt->p << endl;
		pre(rt->c[0]);
		cout << rt->x << ' ';
		pre(rt->c[1]);
	}
} spt;

VP rec(N);
int run() {
	int n, m;
	while (cin >> n >> m) {
		init();
		for (int i = 0; i < n; ++i) cin >> rec[i].x >> rec[i].y;
		spt.build(rec, n);
		//spt.pre();
		char op[3];
		int x, y, z;
		for (int i = 0; i < m; ++i) {
			cin >> op;
			//cout << op << endl;
			if ('Q' == *op) {
				cin >> x >> y >> z;
				cout << spt.get_gcd(x, y, z) << endl;
			} else if ('I' == *op) {
				cin >> x >> y >> z;
				spt.insert(PII(y, z), x);
			} else if ('D' == *op) {
				cin >> x;
				spt.erase(x);
			} else if ('R' == *op) {
				cin >> x;
				spt.change(x);
			} else {
				cin >> x >> y;
				spt.modify(y, x);
			}
			//spt.pre();
			//cout << op << "ok" << endl;
		}
	}
	return 0;
}

int main() {
	//freopen("in_i", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
