#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const LL K1 = 37;
const LL M1 = 1e4 + 7;
const LL K2 = 131;
const LL M2 = 1e9 + 7;
const int N = 55555;

char str[N];
LL s1[N], s2[N], ep1[N], ep2[N];
int len;

void PRE() {
	ep1[0] = ep2[0] = 1;
	for (int i = 1; i < N; i++) {
		ep1[i] = ep1[i - 1] * K1 % M1;
		ep2[i] = ep2[i - 1] * K2 % M2;
	}
}

inline int decode(char c) { return c - 'A' + 1; }

void get_hash(char *s) {
	s1[0] = decode(s[0]) % M1;
	s2[0] = decode(s[0]) % M2;
	for (int i = 1; i < len; i++) {
		s1[i] = (s1[i - 1] + decode(s[i]) * ep1[i] % M1) % M1;
		s2[i] = (s2[i - 1] + decode(s[i]) * ep2[i] % M2) % M2;
	}
}

typedef pair<LL, LL> PII;

PII test(int l, int r) {
	LL k1, k2;
	if (l == 0) k1 = s1[r], k2 = s2[r];
	else k1 = (s1[r] - s1[l - 1] + M1) % M1, k2 = (s2[r] - s2[l - 1] + M2) % M2;
	int d = len - l;
	return PII(k1 * ep1[d] % M1, k2 * ep2[d] % M2);
}

bool test(int l1, int r1, int l2, int r2) { return test(l1, r1) == test(l2, r2); }

int work() {
	int l = 0, r = len - 1, k, ans = 0;
	while (1) {
		k = 0;
		while (!test(l, l + k, r - k, r)) k++;
		if (k == r - l) {
			ans++;
			break;
		} else ans += 2;
		l += k + 1, r -= k + 1;
		if (l > r) break;
	}
	return ans;
}

int main() {
	//freopen("in", "r", stdin);
	int _;
	PRE();
	scanf("%d", &_);
	for (int cas = 1; cas <= _; cas++) {
		scanf("%s", str);
		len = strlen(str);
		get_hash(str);
		printf("Case #%d: %d\n", cas, work());
	}
	return 0;
}

