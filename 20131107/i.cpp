#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int kind = 38;
int w[256];
int n, m;

struct Node {
	int child[kind], cnt, fa;
	char ch;
	void init() {
		memset(child, 0, sizeof(child));
		cnt = 0;
	}
} node[188888];

int record;
struct Trie {
	int root, tot;
	void clear() {
		root = tot = 0;
		node[root].init();
		node[root].fa = -1;
	}
	void insert(char *str) {
		int p = root;
		while (*str) {
			int idx = w[*str];
			if (!node[p].child[idx]) {
				node[p].child[idx] = ++tot;
				node[tot].init();
				node[tot].fa = p;
				node[tot].ch = *str;
			}
			p = node[p].child[idx];
			str++;
		}
		node[p].cnt = 1;
	}
	int query(int p, char *str) {
		if (*str == 0) {
			int res = node[p].cnt;
			if (res) { record = p; }
			for (int i = 0; i < kind - 1; i++) {
				if (node[p].child[i]) res += query(node[p].child[i], str);
			}
			return res;
		}
		if (*str != '/' && node[p].child[w[*str]]) {
			return query(node[p].child[w[*str]], str + 1);
		} else if (*str == '/') {
			int res = 0;
			for (int i = 0; i < kind; i++) {
				if (node[p].child[i]) res += query(node[p].child[i], str + (i == w['/']));
			}
			return res;
		} return 0;
	}
} trie;

char str[555];
char que[555];

int main() {
	for (char ch = 'a'; ch <= 'z'; ch++) w[ch] = ch - 'a';
	for (char ch = '0'; ch <= '9'; ch++) w[ch] = 26 + ch - '0';
	w['.'] = 36; w['/'] = 37;

	while (~scanf("%d", &n)) {
		trie.clear();
		for (int i = 0; i < n; i++) {
			scanf("%s", str);
			trie.insert(str);
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s", str);
			int ret = trie.query(0, str);
			if (ret != 1) printf("%d\n", ret);
			else {
				int x = record;
				int alloc = 0;
				while (x) {
					que[alloc++] = node[x].ch;
					x = node[x].fa;
				}
				for (int i = alloc - 1; i >= 0; i--) {
					putchar(que[i]);
				}
				puts("");
			}
		}
	}
	return 0;
}
