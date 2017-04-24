#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> Node;
#define x first
#define y second
const LL KEY1 = 97;
const LL MOD1 = 1600033;
const LL KEY2 = 159;
const LL MOD2 = 1e9 + 7;
const int N = 1 << 13;

LL HASH1[N], HASH2[N];
inline int getIdx(const char a) { return a - 'A' + 1; }

bool check(const string &s) {
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] != s[s.length() - i - 1]) return 0;
	}
	return 1;
}

int bruteForce(const string &s) {
	set<string> str;
	for (int i = 0; i < s.length(); ++i) {
		for (int j = 1; j <= s.length() - i; ++j) {
			if (check(s.substr(i, j))) {
				str.insert(s.substr(i, j));
			}
		}
	}
	return str.size();
}

int solve(const string &s) {
	set<Node> hashcodes;
	for (int i = 0; i < s.length(); ++i) { // odd
		int l, r;
		l = r = i;
		stack<Node> temp;
		Node current(getIdx(s[i]), getIdx(s[i]));
		temp.push(current);
		while (l > 0 && r < s.length() - 1 && s[l - 1] == s[r + 1]) {
			--l, ++r;
			current.x = (current.x * KEY1 + getIdx(s[l]) * HASH1[r - l] + getIdx(s[r])) % MOD1;
			current.y = (current.y * KEY2 + getIdx(s[l]) * HASH2[r - l] + getIdx(s[r])) % MOD2;
			temp.push(current);
		}
		while (!temp.empty()) {
			if (hashcodes.find(temp.top()) == hashcodes.end()) hashcodes.insert(temp.top());
			else break;
			temp.pop();
		}
	}
	for (int i = 0; i < s.length() - 1; ++i) { // even
		int l, r;
		l = i, r = i + 1;
		if (s[l] != s[r]) continue;
		stack<Node> temp;
		Node current((getIdx(s[i]) * KEY1 + getIdx(s[i + 1])) % MOD1, (getIdx(s[i]) * KEY2 + getIdx(s[i + 1])) % MOD2);
		temp.push(current);
		while (l > 0 && r < s.length() - 1 && s[l - 1] == s[r + 1]) {
			--l, ++r;
			current.x = (current.x * KEY1 + getIdx(s[l]) * HASH1[r - l] + getIdx(s[r])) % MOD1;
			current.y = (current.y * KEY2 + getIdx(s[l]) * HASH2[r - l] + getIdx(s[r])) % MOD2;
			temp.push(current);
		}
		while (!temp.empty()) {
			if (hashcodes.find(temp.top()) == hashcodes.end()) hashcodes.insert(temp.top());
			else break;
			temp.pop();
		}
	}
	return hashcodes.size();
}

int run() {
	string buffer;
	for (int i = HASH1[0] = 1; i < N; ++i) HASH1[i] = HASH1[i - 1] * KEY1 % MOD1;
	for (int i = HASH2[0] = 1; i < N; ++i) HASH2[i] = HASH2[i - 1] * KEY2 % MOD2;
	while (cin >> buffer) {
		cout << solve(buffer) << endl;
		//cout << bruteForce(buffer) << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	freopen("palindromes.in", "r", stdin);
	freopen("palindromes.out", "w", stdout);
	return run();
}
