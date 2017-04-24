#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, DB> Point;
typedef pair<DB, int> Segment;
#define x first
#define y second
Point ball, direction, field;
istream &operator >> (istream &in, Point &a) { in >> a.x >> a.y; return in; }
const int N = 1 << 7;
const DB EPS = 1e-10;
DB w[N], d[N];

DB calculate(const vector<Segment> &seg, const DB &y) {
	DB sum = 0, total = 0;
	for (int i = 0; i < seg.size(); ++i) {
		if (total + EPS > y) break;
		if (seg[i].y == 0) {
			sum += min(seg[i].x, y - total);
		}
		total += seg[i].x;
	}
	return sum;
}

DB calculate() {
	DB x, sum = 0;
	int k;
	cin >> x >> k;
	for (int i = 1; i <= k; ++i) {
		cin >> w[i];
		sum += w[i];
	}
	for (int i = 1; i < k; ++i) {
		cin >> d[i];
		sum += d[i];
	}
	d[0] = d[k] = field.y - sum;
	DB y = ball.y + direction.y / direction.x * x;
	vector<Segment> temp(k << 1);
	for (int i = 0; i < k; ++i) {
		temp[i << 1] = Segment(w[i + 1], 1);
		temp[i << 1 | 1] = Segment(d[i + 1], 0);
	}
	sum = calculate(temp, y) + d[0];
	for (int i = 0; i < k; ++i) {
		temp[i << 1] = Segment(d[i], 0);
		temp[i << 1 | 1] = Segment(w[i + 1], 1);
	}
	sum -= calculate(temp, y);
	return sum / d[0];
}

int run() {
	int _;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		cin >> field >> ball >> direction;
		DB answer = 1;
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i) {
			answer *= calculate();
		}
		cout << "Case #" << cas << ": " << answer << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(5);
	return run();
}
