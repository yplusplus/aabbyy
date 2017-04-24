#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

template<class T> T sqr(T x) { return x * x;}
typedef pair<double, double> Point;
#define x first
#define y second

const int N = 21;
const double FINF = 1e33;
inline double dist(Point a, Point b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));}
void get(Point &pt) { cin >> pt.x >> pt.y;}
Point pt[N], O;
typedef pair<double, int> Node;

double sum[1 << N];
bool vis[1 << N];
int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(2);
	int T, n, cas = 1;
	cin >> T;
	while (T--) {
		get(O);
		cin >> n;
		n <<= 1;
		for (int i = 0; i < n; i++) get(pt[i]);
		for (int i = 0, e = 1 << n; i < e; i++) sum[i] = FINF, vis[i] = 0;
		sum[0] = 0;
		vis[0] = 1;
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int cur = q.front(), t = cur;
			q.pop();
			int f = 0;
			while (t & 1) t >>= 1, f++;
			for (int i = 0; i < n; i++) {
				if (i == f) continue;
				if ((1 << f | 1 << i) & cur) continue;
				double tmp = min(dist(O, pt[f]) + dist(pt[f], pt[i]), dist(O, pt[i]) + dist(pt[f], pt[i]));
				sum[cur | 1 << f | 1 << i] = min(sum[cur | 1 << f | 1 << i], sum[cur] + tmp);
				if (vis[cur | 1 << f | 1 << i]) continue;
				q.push(cur | 1 << f | 1 << i);
				vis[cur | 1 << f | 1 << i] = 1;
			}
		}
		cout << "Case #" << cas++ << ": " << sum[(1 << n) - 1] << endl;
	}
	return 0;
}
