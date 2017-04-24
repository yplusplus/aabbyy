#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<int, int> Interval;
typedef vector<Interval> Intervals;
typedef vector<DB> Array;
#define a first
#define b second

const int UPPER = 1440 * 60;
const int T = 1 << 6;
inline int min2Sec(const int a) { return a * 60; }

bool check(const Intervals &interval, const DB &d) {
	Array timeMark(interval.size());
	timeMark[0] = interval[0].a;
	for (int i = 1; i < interval.size(); ++i) {
		DB nextTime = timeMark[i - 1] + d;
		if (interval[i].b < nextTime) {
			return 0;
		}
		if (nextTime < interval[i].a) {
			timeMark[i] = interval[i].a;
		} else {
			timeMark[i] = nextTime;
		}
	}
	return 1;
}

bool test(Intervals &interval, const DB &d) {
	sort(interval.begin(), interval.end());
	do {
		if (check(interval, d)) {
			return 1;
		}
	} while (next_permutation(interval.begin(), interval.end()));
	return 0;
}

DB binarySearch(Intervals &interval) {
	DB l = 0, r = UPPER, m;
	for (int i = 0; i < T; ++i) {
		m = (l + r) / 2;
		if (test(interval, m)) {
			l = m;
		} else {
			r = m;
		}
	}
	//cout << "Answer " << m << endl;
	return m;
}

int run() {
	int n, a, b, cas = 0;
	while (cin >> n && n) {
		Intervals interval(n);
		for (int i = 0; i < n; ++i) {
			cin >> a >> b;
			interval[i] = Interval(min2Sec(a), min2Sec(b));
		}
		int answer = int(floor(binarySearch(interval) + 0.5));
		cout << "Case " << ++cas << ": " << (answer / 60) << ':';
		cout.width(2); cout.fill('0'); cout << (answer % 60) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cout << setiosflags(ios::fixed) << setprecision(2);
	return run();
}
