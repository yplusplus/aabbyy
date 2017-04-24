#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
typedef vector<Point> Points;
typedef vector<DB> Array;
const DB PI = acos(-1.0);
#define x first
#define y second
Point operator - (const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
inline DB cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline DB veclen(const Point &a) { return hypot(a.x, a.y); }

void andwer(Points &pt, Points &ch) {
	sort(pt.begin(), pt.end());
	ch.clear();
	if (pt.size() == 0) return ;
	int m = 0;
	for (int i = 0; i < pt.size(); ++i) {
		while (m > 1 && cross(ch[m - 1] - ch[m - 2], pt[i] - ch[m - 2]) <= 0) {
			ch.pop_back();
			--m;
		}
		ch.push_back(pt[i]);
		++m;
	}
	int k = m;
	for (int i = pt.size() - 2; i >= 0; --i) {
		while (m > k && cross(ch[m - 1] - ch[m - 2], pt[i] - ch[m - 2]) <= 0) {
			ch.pop_back();
			--m;
		}
		ch.push_back(pt[i]);
		++m;
	}
	if (m) {
		ch.pop_back();
		--m;
	}
}

DB getLength(Points &pt) {
	if (pt.size() == 0) return 0.0;
	int n = pt.size();
	pt.push_back(pt[0]);
	DB sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += veclen(pt[i] - pt[i + 1]);
	}
	pt.pop_back();
	return sum;
}

int run() {
	int n, cas = 0;
	DB m;
	while (cin >> n >> m && (n || m != 0)) {
		Points pt(n), temp, ch;
		for (int i = 0; i < n; ++i) {
			cin >> pt[i].x >> pt[i].y;
		}
		Array length(1 << n);
		for (int i = 0; i < (1 << n); ++i) {
			temp.clear();
			for (int j = 0; j < n; ++j) {
				if (i & 1 << j) {
					temp.push_back(pt[j]);
				}
			}
			//for (int i = 0; i < temp.size(); ++i) { cout << temp[i].x << ' ' << temp[i].y << endl; }
			andwer(temp, ch);
			//for (int i = 0; i < ch.size(); ++i) { cout << "ch " << ch[i].x << ' ' << ch[i].y << endl; }
			length[i] = getLength(ch) + 2 * PI * m;
			//cout << i << ' ' << length[i] << endl;
		}
		Array dp(1 << n, DBL_MAX);
		dp[0] = 0;
		for (int i = 1; i < (1 << n); ++i) {
			for (int j = (i - 1) & i; ; j = (j - 1) & i) {
				//cout << i << ' ' << j << endl;
				dp[i] = min(dp[j] + length[i ^ j], dp[i]);
				if (j == 0) {
					break;
				}
			}
			//cout << i << ' ' << dp[i] << endl;
		}
		cout << "Case " << ++cas << ": length = " << dp[(1 << n) - 1] << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(2);
	return run();
}
