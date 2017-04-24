#include <bits/stdc++.h>
using namespace std;

const int N = 133333 << 1;
int fa[N];
int ans[N];
int n, m;
struct Node {
	Node *l, *r;
	int size;
	int key, weight;
	Node() {}
	Node(int key, int weight, Node *l, Node *r) : key(key), weight(weight), l(l), r(r) {
		push_up();
	}
	void push_up() {
		size = 1 + lsize() + rsize();
	}
	int lsize() { return l ? l->size : 0; }
	int rsize() { return r ? r->size : 0; }
} *root[N], mem[N];

int alloc;
Node *new_node(int key, int weight, Node *l, Node *r) {
	mem[++alloc] = Node(key, weight, l, r);
	return &mem[alloc];
}

Node *merge(Node *l, Node *r) {
	if (l == NULL || r == NULL) return l ? l : r;
	if (l->weight < r->weight) {
		l->r = merge(l->r, r);
		l->push_up();
		return l;
	} else {
		r->l = merge(l, r->l);
		r->push_up();
		return r;
	}
}

void split(Node *p, Node *&a, Node *&b, int size) {
	assert(size >= 0 && size <= p->size);
	if (size == p->size) { a = p, b = NULL; return; }
	if (size == 0) { a = NULL, b = p; return; }
	if (p->lsize() >= size) {
		b = p;
		split(p->l, a, b->l, size);
		b->push_up();
	} else {
		a = p;
		split(p->r, a->r, b, size - 1 - p->lsize());
		a->push_up();
	}
}

void init() {
	for (int i = 0; i < N; i++) {
		fa[i] = i;
	}
	memset(root, 0, sizeof(root));
}

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void dfs(int start, int offset, Node *p) {
	assert(p != NULL);
	if (p->l) {
		dfs(start, offset, p->l);
	}
	ans[start + offset + p->lsize()] = p->key;
	if (p->r) {
		dfs(start, offset + p->lsize() + 1, p->r);
	}
}

int main() {
	int first = 1;
	srand(time(0));
	int T;
	scanf("%d", &T);
	while (T--) {
		if (first) first = 0;
		else puts("");
		scanf("%d%d", &n, &m);
		init();
		alloc = 0;
		for (int i = 1, x; i <= n; i++) {
			scanf("%d", &x);
			int r = find(x);
			if (root[r] == NULL) {
				root[r] = new_node(i, rand(), NULL, NULL);
			} else {
				int L = r, R = r + root[r]->size - 1;
				Node *a, *b;
				split(root[r], a, b, x - L);
				root[r] = merge(a, new_node(i, rand(), NULL, NULL));
				root[r] = merge(root[r], b);
				int rroot = find(r + root[r]->size - 1);
				root[r] = merge(root[r], root[rroot]);
				fa[rroot] = r;
			}
			if (r > 1) {
				int tmp = find(r - 1);
				if (!(tmp == r - 1 && !root[tmp])) {
					root[tmp] = merge(root[tmp], root[r]);
					fa[r] = tmp;
					r = tmp;
				}
			}
			if (r + 1 < N) {
				int tmp = find(r + root[r]->size);
				if (!(tmp == r + root[r]->size && !root[tmp])) {
					root[r] = merge(root[r], root[tmp]);
					fa[tmp] = r;
				}
			}
		}
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i < N; i++) {
			if (fa[i] == i && root[i]) {
				dfs(i, 0, root[i]);
			}
		}
		int end;
		for (int i = N - 1; i; i--) {
			if (ans[i]) { end = i; break; }
		}
		printf("%d\n", end);
		for (int i = 1; i <= end; i++) {
			printf("%d%c", ans[i], i == end ? '\n' : ' ');
		}
	}
	return 0;
}

