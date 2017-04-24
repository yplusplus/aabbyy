#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef long long LL;
typedef double DB;
typedef pair<LL, LL> PLL;
const DB EPS = 1e-8;
inline int getSign(const DB &a) { return (a > EPS) - (a < -EPS); }

struct Node {
	DB x;
	PLL y;
	Node() {}
	Node(DB x, PLL y) : x(x), y(y) {}
	bool operator < (const Node &a) const {
		if (getSign(x - a.x) == 0) return y < a.y;
		return a.x < x;
	}
} ;

const int LENGTH = 100;
const LL AMPLE = 1e5;
inline DB getIntersect(const PLL &a, const PLL &b) { return DB(a.x * a.y - b.x * b.y) / (a.y - b.y); }
inline DB getDepart(const PLL &a) { return DB(a.x * a.y + LENGTH) / a.y; }
map<PLL, int> number;
set<Node> visit;
int answer, totalCount;

void gao(const pair<PLL, int> &a) {
	DB departTime = getDepart(a.x), temp;
	map<LL, int> timeStamp;
	for (set<Node>::iterator si = visit.begin(); si != visit.end(); ++si) {
		if (getSign(si->x - departTime) < 0) break;
		temp = getIntersect(a.x, si->y);
		DB dist = (temp - a.x.x) * a.x.y;
		if (getSign(0 - dist) > 0 || getSign(dist - 100) > 0) continue;
		answer = max((timeStamp[LL((temp + EPS) * AMPLE)] += number[si->y]) + a.y, answer);
		++totalCount;
	}
	visit.insert(Node(getDepart(a.x), a.x));
}

void print(const pair<PLL, int> &a) { cout << a.x.x << ' ' << a.x.y << ' ' << a.y << endl; }

int run() {
	int n, x, y;
	while (cin >> n) {
		number.clear();
		visit.clear();
		answer = totalCount = 0;
		for (int i = 0; i < n; ++i) {
			cin >> x >> y;
			//x = i / 100 + 1, y = i % 100 + 1;
			answer = max(++number[PLL(x, y)], answer);
		}
		//for_each(number.begin(), number.end(), print);
		for_each(number.begin(), number.end(), gao);
		cout << answer << endl;
		//cout << totalCount << endl;
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
