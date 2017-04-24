#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
typedef pair<LL, LL> Point;
typedef pair<DB, DB> PDD;
typedef pair<LL, PDD> Node;
typedef vector<Point> VP;
typedef vector<Node> VN;
#define x first
#define y second
VP front, side;
VN frontNode, sideNode;
int n, m;
const DB EPS = 1e-10;
const int getSign(const DB &a) { return (a > EPS) - (a < -EPS); }
inline bool cmp(const Node &a, const Node &b) { return a.x > b.x; }

template <class T> inline T sqr(const T &a) { return a * a; }
template <class T> inline T tri(const T &a) { return a * a * a; }
inline DB calculate(const DB &k1, const DB &b1, const DB &k2, const DB &b2, const DB &x) { return k1 * k2 * tri(x) / 3 + (k1 * b2 + k2 * b1) * sqr(x) / 2 + b1 * b2 * x; }

bool work(DB &ans) {
	ans = 0;
	int tn, tm;
	tn = tm = 0;
	frontNode.resize(n << 1);
	for (int i = 1; i < n; ++i) {
		if (front[i - 1].y == front[i].y) continue;
		if (front[i - 1].y > front[i].y) {
			frontNode[tn++] = Node(front[i - 1].y, PDD((DB) (front[i].x - front[i - 1].x) / (front[i - 1].y - front[i].y), front[i - 1].x));
			frontNode[tn++] = Node(front[i].y, PDD((DB) (front[i - 1].x - front[i].x) / (front[i - 1].y - front[i].y), -front[i].x));
		} else {
			frontNode[tn++] = Node(front[i].y, PDD((DB) (front[i].x - front[i - 1].x) / (front[i].y - front[i - 1].y), -front[i].x));
			frontNode[tn++] = Node(front[i - 1].y, PDD((DB) (front[i - 1].x - front[i].x) / (front[i].y - front[i - 1].y), front[i - 1].x));
		}
	}
	sideNode.resize(m << 1);
	for (int i = 1; i < m; ++i) {
		if (side[i - 1].y == side[i].y) continue;
		if (side[i - 1].y > side[i].y) {
			sideNode[tm++] = Node(side[i - 1].y, PDD((DB) (side[i].x - side[i - 1].x) / (side[i - 1].y - side[i].y), side[i - 1].x));
			sideNode[tm++] = Node(side[i].y, PDD((DB) (side[i - 1].x - side[i].x) / (side[i - 1].y - side[i].y), -side[i].x));
		} else {
			sideNode[tm++] = Node(side[i].y, PDD((DB) (side[i].x - side[i - 1].x) / (side[i].y - side[i - 1].y), -side[i].x));
			sideNode[tm++] = Node(side[i - 1].y, PDD((DB) (side[i - 1].x - side[i].x) / (side[i].y - side[i - 1].y), side[i - 1].x));
		}
	}
	sort(frontNode.begin(), frontNode.begin() + tn, cmp);
	sort(sideNode.begin(), sideNode.begin() + tm, cmp);
	if (frontNode[0].x != sideNode[0].x) return 0;
	int i, j;
	i = j = 0;
	DB currentFront = 0, currentSide = 0;
	DB lastFront = 0, lastSide = 0;
	DB frontK = 0, sideK = 0;
	LL currentHeight = frontNode[0].x, lastHeight;
	while (i < tn || j < tm) {
		lastHeight = currentHeight;
		currentHeight = 0;
		if (i < tn) currentHeight = max(frontNode[i].x, currentHeight);
		if (j < tm) currentHeight = max(sideNode[j].x, currentHeight);
		DB delta = lastHeight - currentHeight;
		currentFront += delta * frontK;
		currentSide += delta * sideK;
		ans += calculate(frontK, lastFront, sideK, lastSide, delta);
		//cout << "front " << i << ' ' << lastFront << ' ' << currentFront << ' ' << frontK << ' ' << delta << endl;
		//cout << "side " << j << ' ' << lastSide << ' ' << currentSide << ' ' << sideK << ' ' << delta << endl;
		while (i < tn && currentHeight == frontNode[i].x) {
			frontK += frontNode[i].y.x;
			currentFront += frontNode[i].y.y;
			++i;
		}
		while (j < tm && currentHeight == sideNode[j].x) {
			sideK += sideNode[j].y.x;
			currentSide += sideNode[j].y.y;
			++j;
		}
		lastFront = currentFront;
		lastSide = currentSide;
		//cout << "front " << i << ' ' << lastFront << ' ' << currentFront << ' ' << frontK << ' ' << delta << endl;
		//cout << "side " << j << ' ' << lastSide << ' ' << currentSide << ' ' << sideK << ' ' << delta << endl;
		//cout << ans << endl;
	}
	return 1;
}

bool input() {
	cin >> n;
	if (cin.eof()) return 0;
	front.resize(n);
	for (int i = 0; i < n; ++i) cin >> front[i].x >> front[i].y;
	cin >> m;
	if (cin.eof()) return 0;
	side.resize(m);
	for (int i = 0; i < m; ++i) cin >> side[i].x >> side[i].y;
	return 1;
}

int run() {
	while (input()) {
		DB ans;
		if (work(ans)) cout << ans << endl;
		else cout << "Invalid plan" << endl;
	}
	return 0;
}

int main() {
	freopen("lonely.in", "r", stdin);
	freopen("lonely.out", "w", stdout);
	cout << setiosflags(ios::fixed) << setprecision(10);
	ios::sync_with_stdio(0);
	return run();
}
