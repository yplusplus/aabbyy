#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int N = 111111;
const int K = 26;
typedef vector<int> VI;

struct Trie {
	struct Node {
		Node *nx[K], *fail;
		VI end;
		void init() {
			for (int i = 0; i < K; i++) nx[i] = 0;
			fail = 0;
			end.clear();
		}
	} node[N];
	Node *rt;
	int ttnode;
	Node *mem() {
		node[ttnode].init();
		return node + ttnode++;
	}
	void init() {
		ttnode = 0;
		rt = mem();
	}
	void insert(char *s, int t) {
		int idx;
		Node *p = rt;
		while (*s && *s != '?') {
			idx = *s - 'a';
			if (p->nx[idx] == 0) p->nx[idx] = mem();
			p = p->nx[idx], s++;
		}
		p->end.push_back(t);
	}
	Node *q[N];
	void build() {
		int qh, qt;
		qh = qt = 0;
		rt->fail = rt;
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
					Node *np = p->fail;
					while (np != rt && np->nx[i] == 0) np = np->fail;
					np = np->nx[i];
					if (!np) np = rt;
					p->nx[i]->fail = np;
					q[qt++] = p->nx[i];
					for (VI::iterator vi = np->end.begin(); vi != np->end.end(); vi++) p->nx[i]->end.push_back(*vi);
				}
			}
		}
	}
	map<int, int> cnt;
	int find(char *s, int n) {
		cnt.clear();
		Node *p = rt;
		int idx;
		for (int i = 0; s[i]; i++) {
			idx = s[i] - 'a';
			while (p != rt && p->nx[idx] == 0) p = p->fail;
			p = p->nx[idx];
			if (!p) p = rt;
			for (VI::iterator vi = p->end.begin(); vi != p->end.end(); vi++) {
				if (i - *vi >= 0) {
					cnt[i - *vi]++;
					if (cnt[i - *vi] == n) return i + 1;
				}
			}
		}
		return -1;
	}
	int cal(char *s1, char *s2) {
		init();
		char *s, *t;
		int n = 0, l = strlen(s2), c = 0;
		t = s2 + l - 1;
		while (t >= s2 && *t == '?') t--, c++;
		if (c == l) return c;
		s = s2;
		while (1) {
			while (*s && *s == '?') s++;
			if (!*s) break;
			else {
				t = s;
				while (*t && *t != '?') t++;
				insert(s, t - s2 - 1);
				//cout << "sub " << s << endl;
				n++;
			}
			s = t;
		}
		build();
		int ret = find(s1, n);
		if (ret < 0) return ret;
		return ret + c;
	}
} trie;

bool check(char *s, char *t) {
	char *a = s, *b = t;
	int la = strlen(a), lb = strlen(b);
	char *ea = a + la - 1, *eb = b + lb - 1;
	while (*a && *b && (*a == *b || *b == '?') && *b != '*') a++, b++;
	while (ea >= a && eb >= b && (*ea == *eb || *eb == '?') && *eb != '*') ea--, eb--;
	if (ea < a) {
		while (b <= eb) { if (*b != '*') return 0; b++; }
		return 1;
	}
	if (eb < b) return 0;
	if (*b != '*' || *eb != '*') return 0;
	char *p = b, *q;
	while (p <= eb) { if (*p == '*') *p = 0; p++; }
	p = b, q = a;
	while (1) {
		while (p <= eb && *p == 0) p++;
		if (p > eb) break;
		int c = trie.cal(q, p);
		if (c < 0 || q + c > ea + 1) return 0;
		while (p <= eb && *p) p++;
		q += c;
	}
	return 1;
}

char s1[N], s2[N];
int main() {
	while (cin >> s1 >> s2) {
		if (check(s1, s2)) puts("YES");
		else puts("NO");
	}
	return 0;
}

/*
abcdef
a*c*f

aaaabaaaa
*a?b*a

aaaabaaaa
??*ba*??

abababcdababcdecdabefcdabef
*ab??cd??ef*

abcdebcdde
*abcd?e*

aaaaaa
?*?*??*?*?*?

aabbaabb
*baa*?bb*

ababaabab
?*??*ba??ba??*

ababaabab
?b*?*ba?b?b*

aabababaaa
??*?a?*?a?*?*?*

aabababaaa
??*?a?*?a?*?*

aabbaaabbb
*?*ab*ab*?*

aabbaaabbb
?*?*ab*ab*?*

a
?
*/






