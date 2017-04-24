#include <bits/stdc++.h>

using namespace std;

int getTime(const string &str) {
	int h, m, s;
	sscanf(str.c_str(), "%d:%d:%d", &h, &m, &s);
	return (h * 60 + m) * 60 + s;
}

typedef pair<int, int> PII;
typedef vector<PII> VII;
const int N = 1 << 15;
int ans[N];

int main() {
    //freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	int T;
	cin >> T;
	for (int cas = 1; cas <= T; ++cas) {
		int n, l;
		cin >> n >> l;
		VII student(n);
		string tmp;
		for (int i = 0; i < n; ++i) {
			cin >> tmp;
			student[i] = PII(getTime(tmp), i + 1);
		}
		sort(student.begin(), student.end());
		int tt = 0, last = -l;
		for (int i = 0; i < n; ++i) {
			if (student[i].first - last >= l) {
				last = student[i].first;
				ans[tt++] = student[i].second;
			}
		}
		cout << tt << endl;
		sort(ans, ans + tt);
		for (int i = 0; i < tt; ++i) {
			if (i) cout.put(' ');
			cout << ans[i];
		}
		cout << endl;
	}
	return 0;
}