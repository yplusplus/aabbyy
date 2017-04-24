#include <bits/stdc++.h>
using namespace std;

inline bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
	if (a.first != b.first) return a.first > b.first;
	return a.second < b.second;
}

inline double fix(const double &x) { return int(x * 100 + 0.5) / 100.0; }

int run() {
	int n, m;
	while (cin >> n >> m) {
		vector<string> name(n);
		vector<int> countVotation(n, 0);
		for (int i = 0; i < n; ++i) cin >> name[i];
		int countInvalid = 0;
		string votation;
		for (int i = 0; i < m; ++i) {
			cin >> votation;
			int c = 0, id = 0;
			//cout << votation << endl;
			for (int j = 0; j < n; ++j) {
				if (votation[j] == 'X') {
					++c;
					id = j;
				}
			}
			if (c != 1) {
				++countInvalid;
				continue;
			} else ++countVotation[id];
		}
		vector<pair<int, int> > result(n);
		for (int i = 0; i < n; ++i) {
			result[i].first = countVotation[i];
			result[i].second = i;
		}
		sort(result.begin(), result.end(), cmp);
		for (int i = 0; i < n; ++i) {
			cout << name[result[i].second] << ' ' << fix(result[i].first * 100.0 / m) << '%' << endl;
		}
		cout << "Invalid" << ' ' << fix(countInvalid * 100.0 / m) << '%' << endl;
	}
	return 0;
}

int main() {
	freopen("bad.in", "r", stdin);
	freopen("bad.out", "w", stdout);
	cout << setiosflags(ios::fixed) << setprecision(2);
	ios::sync_with_stdio(0);
	return run();
}
