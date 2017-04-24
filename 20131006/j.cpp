#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

const int N = 111111;

struct Node {
	int y, up, dn;
	Node() {}
	Node(int y) : y(y) {}
	Node(int y, int up, int dn) : y(y), up(up), dn(dn) {}
	bool operator < (Node x) const { return y < x.y;}
	bool operator == (Node x) const { return y == x.y;}
} ;

struct Event {
	int x, a, b, id, end;
	Event() {}
	Event(int x, int a, int b, int id, int end) : x(x), a(a), b(b), id(id), end(end) {}
	bool operator < (Event p) const { return x < p.x;}
} event[N << 1];

int ans[N];

int main() {
	int n;
	while (~scanf("%d", &n)) {
		int a, b, c, d;
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d%d", &a, &b, &c, &d);
			if (a > c) swap(a, c);
			if (b > d) swap(b, d);
			event[i << 1] = Event(a, b, d, i, 1);
			event[i << 1 | 1] = Event(c, b, d, i, -1);
		}
		n <<= 1;
		sort(event, event + n);
		set<Node> line;
		memset(ans, -1, sizeof(ans));
		for (int i = 0; i < n; i++) {
			Event &e = event[i];
			//cout << e.x << ' ' << e.a << ' ' << e.b << ' ' << e.id << ' ' << e.end << endl;
			if (e.end == 1) {
				line.insert(Node(e.a));
				line.insert(Node(e.b));
				
				set<Node>::iterator si, ti;
				Node tmp;
				si = line.find(Node(e.a));
				if (si == line.begin()) tmp.up = -1;
				else {
					ti = si;
					ti--;
					tmp.up = ti->dn;
					ans[e.id] = ti->dn;
				}
				tmp.dn = e.id;
				tmp.y = e.a;
				line.erase(Node(e.a));
				line.insert(tmp);

				si = line.find(Node(e.b));
				ti = si;
				ti++;
				if (ti == line.end()) tmp.dn = -1;
				else tmp.dn = ti->up;
				tmp.up = e.id;
				tmp.y = e.b;
				line.erase(Node(e.b));
				line.insert(tmp);
			} else {
				line.erase(Node(e.a));
				line.erase(Node(e.b));
			}
		}
		n >>= 1;
		for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
	}
	return 0;
}
