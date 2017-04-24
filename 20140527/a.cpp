#include <bits/stdc++.h>
using namespace std;

const int N = 444 * 444;
int x[N], y[N];
typedef pair<int, int> PII;

inline PII fix(const PII &a) {
	if (a.first > a.second) return PII(a.second, a.first);
	return a;
}

int main() {
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	int d, r;
	while (cin >> d >> r) {
		cout << "YES" << endl;
		set<PII> answer;
		int r1 = r << 1, tt = 0;
		for (int i = 0; i < r1; ++i) {
			answer.insert(fix(PII(i, (i + 1) % r1)));
		}
		int r2 = (d - r) << 1;
		for (int i = 0; i < r2; ++i) {
			answer.insert(fix(PII(r1 - 1 + i, r1 - 1 + (i + 1) % r2)));
		}
		cout << (r1 + r2 - 1 + (r2 == 0)) << ' ' << answer.size() << endl;
		for (auto it = answer.begin(); it != answer.end(); ++it) {
			cout << (it->first + 1) << ' ' << (it->second + 1) << endl;
		}
	}
	return 0;
}
