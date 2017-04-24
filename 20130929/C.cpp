#include <cctype>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int KEY1 = 10007;
const int MOD1 = 99990001;
const int KEY2 = 50021;
const int MOD2 = 1000000007;
const int N = 111111;

typedef long long LL;
typedef pair<LL, LL> PII;
#define x first
#define y second

LL pow1[N], pow2[N];
void PRE() {
	pow1[0] = pow2[0] = 1;
	for (int i = 1; i < N; i++)
		pow1[i] = pow1[i - 1] * KEY1 % MOD1,
		pow2[i] = pow2[i - 1] * KEY2 % MOD2;
}

inline LL safemod(LL a, LL m) { return (a % m + m) % m;}
inline PII add(PII sum, char c) { return PII((sum.x * KEY1 + c - '0' + 1) % MOD1, (sum.y * KEY2 + c - '0' + 1) % MOD2);}
inline PII sub(PII sum, char c, int len) { return PII(safemod(sum.x - (c - '0' + 1) * pow1[len - 1], MOD1), safemod(sum.y - (c - '0' + 1) * pow2[len - 1], MOD2));}

PII gethash(char *p) {
	PII sum(0, 0);
	while (isdigit(*p)) {
		sum = add(sum, *p);
		p++;
	}
	return sum;
}

int match(char *s, PII key, int min_len) {
	PII cur(0, 0);
	int len = strlen(s);
	if (min_len > len) return -1;
	for (int i = 0; i < min_len; i++) cur = add(cur, s[i]);
	for (int i = min_len; i <= len; i++, i++) {
		//cout << i << ' ' << cur.x << ' ' << cur.y << endl;
		if (cur == key) return i;
		cur = sub(cur, s[i - min_len], min_len);
		cur = add(cur, s[i]);
		cur = sub(cur, s[i + 1 - min_len], min_len);
		cur = add(cur, s[i + 1]);
	}
	return -1;
}

int getlen(char *p) {
	int len = 0;
	while (*p) {
		if (*p == '*') ;
		else len++;
		p++;
	}
	return len;
}

int getsub(char *s) {
	char *p = s;
	while (1) {
		if (*p == 0 || *p == '*' || *p == '#') return p - s;
		p++;
	}
	return -1;
}

char pattern[N], str[N];
int pattern_len;
bool check() {
	int l2 = strlen(str);
	if ((pattern_len ^ l2) & 1) return 0;
	if (pattern_len > l2) return 0;
	int l1 = strlen(pattern);
	char *s1 = pattern, *s2 = str;
	int h1, t1, h2, t2;
	h1 = h2 = 0, t1 = l1 - 1, t2 = l2 - 1;
	while (h1 < l1 && h2 < l2) {
		if (s1[h1] == '*' || s1[h1] == '#') break;
		if (s1[h1] != s2[h2]) return 0;
		h1++, h2++;
	}
	if (h1 == l1 && h2 == l2) return 1;
	while (t1 >= 0 && t2 >= 0) {
		if (s1[t1] == '*' || s1[t1] == '#') break;
		if (s1[t1] != s2[t2]) return 0;
		t1--, t2--;
	}
	if (h1 > t1) return 0;
	if (h2 == l2) {
		while (h1 < l1) {
			if (s1[h1] != '*') return 0;
			h1++;
		}
		return 1;
	}
	if (t2 == -1) {
		while (t1 >= 0) {
			if (s1[t1] != '*') return 0;
			t1--;
		}
		return 1;
	}
	//cout << h1 << ' ' << t1 << ' ' << h2 << ' ' << t2 << endl;
	PII key;
	int seg_len;
	while (h1 <= t1 && h2 <= t2) {
		int cnt = 0;
		while (h1 <= t1) {
			if (s1[h1] != '*' && s1[h1] != '#') break;
			if (s1[h1] == '#') cnt++;
			h1++;
		}
		if (h1 > t1) {
			int _1 = cnt, _2 = t2 - h2 + 1;
			if (_1 > _2) return 0;
			if ((_1 ^ _2) & 1) return 0;
			return 1;
		}
		key = gethash(s1 + h1);
		seg_len = getsub(s1 + h1);
		//cout << s1 + h1 << endl;
		h1 += seg_len;
		//cout << key.x << ' ' << key.y << endl;
		int nx = match(s2 + h2 + cnt, key, seg_len);
		if (nx == -1) return 0;
		h2 += cnt + nx;
		//cout << h1 << ' ' << h2 << endl;
		if (h2 > t2 + 1) return 0;
		if (h2 == t2 + 1) {
			while (h1 <= t1) {
				if (s1[h1] != '*') return 0;
				h1++;
			}
			return 1;
		}
	}
	return 1;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	int cas1 = 1, cas2;
	PRE();
	do {
		cas2 = 1;
		cin >> pattern;
		pattern_len = getlen(pattern);
		//cout << "minium length " << pattern_len << endl;
		while (cin >> str) {
			if (!isdigit(*str) && *str != '*' && *str != '#') break;
			cout << cas1 << "." << cas2 << "." << (check() ? " match" : " not") << endl;
			cas2++;
		}
		cas1++;
	} while (strcmp(str, "QUIT"));
	return 0;
}


