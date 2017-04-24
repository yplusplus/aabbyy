#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> Node;
const LL KEY1 = 37;
const LL KEY2 = 159;
const int MOD1 = 1e4 + 7;
const int MOD2 = 1e9 + 7;
#define x first
#define y second

inline int getIdx(char a) {
	if (a == 'A') return 1;
	if (a == 'T') return 2;
	if (a == 'C') return 3;
	if (a == 'G') return 4;
	return -1;
}

Node convert(const string &a) {
	Node temp(0, 0);
	for (int i = 0; i < a.length(); ++i) {
		temp.x = (temp.x * KEY1 + getIdx(a[i])) % MOD1;
		temp.y = (temp.y * KEY2 + getIdx(a[i])) % MOD2;
	}
	return temp;
}

string convert(string &a, int l, int r) {
	while (l < r) {
		swap(a[l], a[r]);
		l++, r--;
	}
	return a;
}

bool solve(string a, string b) {
	set<Node> has;
	int n = a.length();
	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			convert(a, i, j);
			for (int l = 0; l < n; ++l) {
				for (int r = l; r < n; ++r) {
					convert(a, l, r);
					has.insert(convert(a));
					convert(a, l, r);
				}
			}
			convert(a, i, j);
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			convert(b, i, j);
			for (int l = 0; l < n; ++l) {
				for (int r = l; r < n; ++r) {
					convert(b, l, r);
					if (has.find(convert(b)) != has.end()) return 1;
					convert(b, l, r);
				}
			}
			convert(b, i, j);
		}
	}
	return 0;
}

int run() {
	string a, b;
	while (cin >> a >> b) {
		cout << (solve(a, b) ? "Similar" : "Different") << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	freopen("dna.in", "r", stdin);
	freopen("dna.out", "w", stdout);
	return run();
}
