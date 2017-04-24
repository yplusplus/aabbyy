#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<string> VS;
VI dp, preLen, preStr, nx;

void getNext(const string &s, VI &nx) {
	int len = s.length();
	int i, j;
	nx[i = 0] = (j = -1);
	while (i < len) {
		while (j >= 0 && s[i] != s[j]) j = nx[j];
		++i, ++j;
		nx[i] = j;
	}
}

void update(const string &s, const VI &nx, const int offset) {
	int n = s.length();
	for (int i = 1; i <= n; ++i) {
		int len = i - nx[i];
		if (i % len) continue;
		if (dp[offset + i] > dp[offset] + len) {
			dp[offset + i] = dp[offset] + len;
			preStr[offset + i] = len;
			preLen[offset + i] = i;
		}
	}
}

void backTrack(const string &s, int len) {
	stack<string> ansStr;
	stack<int> ansLen;
	while (len > 0) {
		ansStr.push(s.substr(len - preLen[len], preStr[len]));
		ansLen.push(preLen[len]);
		len -= preLen[len];
	}
	while (!ansStr.empty()) {
		string temp = ansStr.top();
		cout << temp << ' ' << (ansLen.top() / temp.length()) << endl;
		ansStr.pop();
		ansLen.pop();
	}
}

void solve(const string &str) {
	int n = str.length();
	dp.clear();
	dp.resize(n + 1, INT_MAX);
	preLen.resize(n + 1);
	preStr.resize(n + 1);
	nx.resize(n + 1);
	dp[0] = 0;
	for (int i = 0; i < n; ++i) {
		string sub = str.substr(i);
		getNext(sub, nx);
		//for (int j = 0; j <= n - i; ++j) cerr << nx[j] << ' '; cerr << endl;
		update(sub, nx, i);
	}
	for (int i = 0; i <= n; ++i) cerr << preStr[i] << ' ' << preLen[i] << endl;
	cout << dp[n] << endl;
	backTrack(str, n);
}

int run() {
	string str;
	while (cin >> str) {
		solve(str);
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	freopen("decomp.in", "r", stdin);
	freopen("decomp.out", "w", stdout);
	return run();
}
