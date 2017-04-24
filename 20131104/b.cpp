#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 11111;
const int L = 22;

int pri[N], last_time[N];
char name[N][L];
map<string, int> id;

struct Node {
	int id, t;
	Node() {}
	Node(int id, int t) : id(id), t(t) {}
	bool operator < (const Node &a) const {
		if (pri[id] != pri[a.id]) return pri[id] > pri[a.id];
		return t > a.t;
	}
	bool operator == (const Node &a) const { return id == a.id && t == a.t; }
} ;

int main() {
	//freopen("in", "r", stdin);
	int _, n, m;
	scanf("%d", &_);
	while (_--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%s%d", name[i], pri + i);
			id[name[i]] = i;
		}
		scanf("%d", &m);
		char op[3], buf[L];
		set<Node> cur;
		for (int i = 1; i <= m; i++) {
			scanf("%s", op);
			if (*op == 'g') {
				if (cur.empty()) puts("<empty>");
				else {
					puts(name[cur.begin()->id]);
					cur.erase(cur.begin());
				}
			} else if (*op == 'a') {
				scanf("%s", buf);
				int t = id[buf];
				cur.insert(Node(t, i));
				last_time[t] = i;
			} else {
				scanf("%s", buf);
				int t = id[buf];
				cur.erase(Node(t, last_time[t]));
			}
		}
	}
	return 0;
}

