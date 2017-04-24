#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector<int> Node;
const int K = 2;
const LL KEY[K] = { 59, 197 };
const int MOD[K] = { int(1e4 + 7), int(1e9 + 7) };

inline int getIdx(char a) { return a - 'A' + 1; }

void hashFunc(const string &s, Node &hashCode) {
	hashCode.clear();
	hashCode.resize(K, 0);
	int len = s.length();
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < K; ++j) {
			hashCode[j] = (hashCode[j] * KEY[j] + getIdx(s[i])) % MOD[j];
		}
	}
}

map<char, string> nx;
map<Node, int> visit;

string toNext(const string &a, int l) {
	int len = a.length();
	string temp;
	for (int i = 0; i < len; ++i) {
		temp += nx[a[i]];
		if (temp.length() >= l) break;
	}
	if (temp.length() > l) return temp.substr(0, l);
	return temp;
}

char work(int k, int p, string s) {
	visit.clear();
	int curTime = 0;
	Node code;
	hashFunc(s, code);
	visit[code] = curTime;
	while (1) {
		if (k <= 0) break;
		s = toNext(s, p);
		++curTime;
		--k;
		//cerr << s << endl;
		hashFunc(s, code);
		if (visit.find(code) != visit.end()) {
			k %= curTime - visit[code];
			break;
		}
		visit[code] = curTime;
	}
	while (k--) {
		s = toNext(s, p);
	}
	if (s.length() >= p) return s[p - 1];
	return '-';
}

int run() {
	int n, k, p;
	while (cin >> n >> k >> p) {
		string init, temp;
		cin >> init;
		nx.clear();
		for (int i = 0; i < n; ++i) {
			cin >> temp;
			nx[i + 'A'] = temp;
		}
		cout << work(k, p, init) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	freopen("morpher.in", "r", stdin);
	freopen("morpher.out", "w", stdout);
	return run();
}
