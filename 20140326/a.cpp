#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 18;
const int MOD = 1e9 + 7;
struct Node {
	char ch;
	int pv, nx;
	Node() {}
	Node(char ch, int pv = -1, int nx = -1) : ch(ch), pv(pv), nx(nx) {}
} node[N];

void erase(Node &p) {
	if (~p.pv) node[p.pv].nx = p.nx;
	if (~p.nx) node[p.nx].pv = p.pv;
}

int work(const string &s) {
	int n = s.length(), ans = 0;
	for (int i = 0; i < n; ++i) {
		node[i].ch = s[i];
		node[i].pv = i - 1;
		node[i].nx = i + 1;
	}
	node[n - 1].nx = -1;
	int cur = n - 1 >> 1;
	for (int i = 0; i < n; ++i) {
		if (n - i & 1) {
			ans <<= 1, ans |= node[cur].ch & 1;
			if (ans >= MOD) ans -= MOD;
			erase(node[cur]);
			cur = node[cur].pv;
		} else {
			int nx = node[cur].nx;
			if (node[cur].ch >= node[nx].ch) {
				ans <<= 1, ans |= node[cur].ch & 1;
				if (ans >= MOD) ans -= MOD;
				erase(node[cur]);
				cur = node[cur].nx;
			} else {
				ans <<= 1, ans |= node[nx].ch & 1;
				if (ans >= MOD) ans -= MOD;
				erase(node[nx]);
			}
		}
	}
	return ans;
}

int run() {
	int _;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		string buf;
		cin >> buf;
		cout << "Case #" << cas << ": " << work(buf) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
