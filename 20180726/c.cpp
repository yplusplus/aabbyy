#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 111111;
struct TreapNode {
    TreapNode() : left_(NULL), right_(NULL) {}
    TreapNode(int key) : key_(key), size_(1), left_(NULL), right_(NULL) {}

    int key_, size_;
    TreapNode *left_, *right_;

    inline int size() const { return size_; }
    inline int lsize() const { return left_ ? left_->size_ : 0; }
    inline int rsize() const { return right_ ? right_->size_ : 0; }

    TreapNode *push_up() {
        size_ = 1 + lsize() + rsize();
        // other push_up operations
        return this;
    }
};
TreapNode nodes[N];

void split(TreapNode *root, int k, TreapNode *&p, TreapNode *&q) {
    if (k == 0) { p = NULL, q = root; return; }
    if (root->size() == k) { p = root, q = NULL; return; }
    if (root->lsize() >= k) {
        q = root;
        split(q->left_, k, p, q->left_);
        q->push_up();
    } else {
        p = root;
        k -= root->lsize() + 1;
        split(p->right_, k, p->right_, q);
        p->push_up();
    }
}

TreapNode *merge(TreapNode *p, TreapNode *q) {
    if (!p || !q) return p ? p : q;
    bool less = rand() % (p->size() + q->size()) < p->size();
    if (less) {
        p->right_ = merge(p->right_, q);
        return p->push_up();
    }

    q->left_ = merge(p, q->left_);
    return q->push_up();
}

// insert = split + merge + merge
// delete = split + split + merge

int tot;
TreapNode *new_node(int x) {
    TreapNode node(x);
    nodes[++tot] = node;
    return &nodes[tot];
}

void output(TreapNode *p, int &n) {
    if (p == NULL) return;
    output(p->left_, n);
    n--;
    printf("%d%c", p->key_, n ? ' ' : '\n');
    output(p->right_, n);
}

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        TreapNode *root = NULL;
        tot = 0;
        for (int i = 1; i <= n; i++) {
            root = merge(root, new_node(i));
        }
        for (int i = 1; i <= m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            TreapNode *left, *right;
            split(root, a - 1, left, right);
            split(right, b, root, right);
            root = merge(root, left);
            root = merge(root, right);
        }
        output(root, n);
    }
    return 0;
}
