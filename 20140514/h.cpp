#include <bits/stdc++.h>
using namespace std;

const int N = 222222;

struct Node {
	int val, mi, weight, size;
	Node *l, *r;
	Node() {}
	Node(int val, int weight, Node *l, Node *r) : val(val), mi(val), weight(weight), size(1), l(l), r(r) {}
	int lsize() { return l ? l->size : 0; }
	int rsize() { return r ? r->size : 0; }
	void push_up() {
		size = 1;
		mi = val;
		if (l) mi = min(mi, l->mi), size += lsize();
		if (r) mi = min(mi, r->mi), size += rsize();
	}
} memory[N];

int alloc;
Node *new_node(int val) {
	++alloc;
	memory[alloc] = Node(val, rand(), NULL, NULL);
	return &memory[alloc];
}

Node *merge(Node *a, Node *b) {
	if (a == NULL || b == NULL) return a ? a : b;
	if (a->weight > b->weight) {
		a->r = merge(a->r, b);
		a->push_up();
		return a;
	} else {
		b->l = merge(a, b->l);
		b->push_up();
		return b;
	}
}

void split(Node *p, Node *&a, Node *&b, int size) {
	if (size == 0) { a = NULL, b = p; return; }
	if (size == p->size) { a = p, b = NULL; return; }
	if (size <= p->lsize()) {
		b = p;
		split(p->l, a, b->l, size);
		b->push_up();
	} else {
		a = p;
		split(p->r, a->r, b, size - p->lsize() - 1);
		a->push_up();
	}
}

void dfs(Node *p) {
	if (p) {
		dfs(p->l);
		cout << p->val << " ";
		dfs(p->r);
	}
}

int main() {
	freopen("rmq.in", "r", stdin);
	freopen("rmq.out", "w", stdout);
	ios::sync_with_stdio(false);
	srand(time(0));
	alloc = 0;
	int n, a, b;
	cin >> n;
	string cmd;
	Node *root = NULL;
	Node *p1, *p2, *p3;
	for (int i = 0; i < n; i++) {
		cin >> cmd >> a >> b;
		if (cmd[0] == '+') {
			split(root, p1, p2, a);
			root = merge(p1, new_node(b));
			root = merge(root, p2);
		} else {
			split(root, p1, p2, a - 1);
			split(p2, p2, p3, b - a + 1);
			cout << p2->mi << endl;
			root = merge(p1, p2);
			root = merge(root, p3);
		}
	}
	return 0;
}
