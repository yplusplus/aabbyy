#include <bits/stdc++.h>
using namespace std;

string str;
bool dfs(int a, int b, int p) {
	if (p <= -1) return 1;
	int c = -1;
	for (int i = 0; i < 3; ++i) if (i != a && i != b) c = i;
	assert(c != -1);
	if (str[p] - 'A' == a) return dfs(a, c, p - 1);
	if (str[p] - 'A' == b) return dfs(b, c, p - 1);
	return 0;
}

int run() {
	int n;
	while (cin >> n) {
		cin >> str;
		cout << (dfs(0, 1, n - 1) ? "YES" : "NO") << endl;
	}
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
