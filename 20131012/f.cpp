#include <ctime>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 111111;
const int K = 2;
int cur_dim, cur;
LL r[N];
template<class T> inline T sqr(T x) { return x * x;}

struct Point {
	LL x[K];
	int id;
	Point *c[2];
	void get() { for (int i = 0; i < K; i++) scanf("%lld", x + i);}
	bool operator < (const Point &a) const {
		for (int i = 0; i < 2; i++)
			if (x[cur_dim + i & 1] != a.x[cur_dim + i & 1])
				return x[cur_dim + i & 1] < a.x[cur_dim + i & 1];
		return 0;
	}
} ;

typedef pair<LL, Point *> Node;
const LL INF = 0x7777777777777777ll;

inline LL dist(const Point &a, const Point &b) {
	LL ret = 0;
	for (int i = 0; i < K; i++) ret += sqr(a.x[i] - b.x[i]);
	return ret;
}

priority_queue<Node> q;
struct KDT {
	Point pt[N], ans[N];
	Point *RT, qry;
	int n, sz;
	void build(int _n) { n = _n; RT = build(0, n - 1, 0);}
	Point *build(int l, int r, int d) {
		if (l > r) return 0;
		int m = l + r >> 1;
		//cout << l << ' ' << r << ' ' << pt[m].x[0] << ' ' << pt[m].x[1] << endl;
		cur_dim = d & 1;
		nth_element(pt + l, pt + m, pt + r + 1);
		pt[m].c[0] = build(l, m - 1, d + 1);
		pt[m].c[1] = build(m + 1, r, d + 1);
		return pt + m;
	}
	void query(const Point &p) {
		while (!q.empty()) q.pop();
		qry = p;
		query(RT, 0);
		sz = 0;
		while (!q.empty()) {
			ans[sz++] = *q.top().second;
			q.pop();
		}
	}
	void query(Point *rt, int d) {
		//cout << d << ' ' << rt << endl;
		LL dis = dist(*rt, qry);
		if (rt->c[0] == 0 && rt->c[1] == 0) {
			if (dis < r[cur]) q.push(Node(dis, rt));
			return ;
		}
		cur_dim = d & 1;
		if (dis < r[cur]) q.push(Node(dis, rt));
		LL mid = rt->x[cur_dim];
		if (rt->c[0] && qry.x[cur_dim] < mid || rt->c[1] == 0) {
			query(rt->c[0], d + 1);
			cur_dim = d & 1;
			if (rt->c[1] && r[cur] > sqr(mid - qry.x[cur_dim])) query(rt->c[1], d + 1);
		} else {
			query(rt->c[1], d + 1);
			cur_dim = d & 1;
			if (rt->c[0] && r[cur] > sqr(mid - qry.x[cur_dim])) query(rt->c[0], d + 1);
		}
	}
} kdt;

Point cir[N];
int ans[N];

int main() {
	//freopen("in", "r", stdin);
	int _, n, m;
	scanf("%d", &_);
	//_ = 1;
	//srand(time(0));
	for (int cas = 1; cas <= _; cas++) {
		scanf("%d", &n);
		//n = 100000;
		for (int i = 0; i < n; i++) {
			//cir[i].x[0] = rand() % 100000;
			//cir[i].x[1] = rand() % 100000;
			//r[i] = 10;
			cir[i].get();
			scanf("%lld", r + i);
			r[i] *= r[i];
		}
		scanf("%d", &m);
		//m = 50000;
		printf("Case #%d:", cas);
		if (m == 0) { cout << endl; continue;}
		for (int i = 0; i < m; i++) {
			ans[i] = 0;
			kdt.pt[i].get();
			//kdt.pt[i].x[0] = i;
			//kdt.pt[i].x[1] = i;
			kdt.pt[i].id = i;
		}
		kdt.build(m);
		for (int i = 0; i < n; i++) {
			cur = i;
			kdt.query(cir[i]);
			int t = kdt.sz;
			//cout << "cir " << i << ' ' << t << endl;
			for (int j = 0; j < t; j++) {
				//cout << kdt.ans[j].x[0] << ' ' << kdt.ans[j].x[1] << endl;
				ans[kdt.ans[j].id]++;
			}
		}
		for (int i = 0; i < m; i++) printf(" %d", ans[i]);
		puts("");
	}
	return 0;
}




