#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

typedef long long LL;
const int N = 111111;
const int MOD = 1000000007;
const int K1 = 159;
const int K2 = 137;

char str[N], tmp[N << 1];
int d[N << 1], len;
LL hash1[N], hash2[N], ep1[N], ep2[N];

void pre() {
	ep1[0] = ep2[0] = 1;
	for (int i = 1; i < N; i++) ep1[i] = ep1[i - 1] * K1, ep1[i] %= MOD;
	for (int i = 1; i < N; i++) ep2[i] = ep2[i - 1] * K2, ep2[i] %= MOD;
}

pair<LL, LL> gethash(int l, int r) {
	LL ret1, ret2;
	if (l == 0) ret1 = hash1[r] * ep1[len] % MOD;
	else ret1 = (hash1[r] - hash1[l - 1] + MOD) % MOD * ep1[len - l] % MOD;
	if (l == 0) ret2 = hash2[r] * ep2[len] % MOD;
	else ret2 = (hash2[r] - hash2[l - 1] + MOD) % MOD * ep2[len - l] % MOD;
	//cout << l << ' ' << r << ' ' << ret << endl;
	return pair<LL, LL>(ret1, ret2);
}

int tot;
void mana(char *s) {
	tot = 0;
	tmp[tot++] = '$';
	//cout << len << endl;
	for (int i = 0; i < len; i++) {
		tmp[tot++] = '*';
		tmp[tot++] = s[i];
	}
	tmp[tot++] = '*';
	tmp[tot] = 0;
	int mx = 0, id = 0;
	for (int i = 1; i < tot; i++) {
		d[i] = mx > i ? min(d[2 * id - i], mx - i) : 1;
		while (tmp[i + d[i]] == tmp[i - d[i]]) d[i]++;
		if (mx < i + d[i]) mx = i + d[i], id = i;
	}
	for (int i = 0; i < tot; i++) d[i]--;
	//for (int i = 1; i < tot; i++) cout << i << ' ' << tmp[i] << ' ' << d[i] << endl;
}

int work(char *s) {
	len = strlen(s);
	// pre-hash
	for (int i = 0; i < len; i++) hash1[i] = (i ? hash1[i - 1] : 0) + (s[i] - 'a' + 1) * ep1[i], hash1[i] %= MOD;
	for (int i = 0; i < len; i++) hash2[i] = (i ? hash2[i - 1] : 0) + (s[i] - 'a' + 1) * ep2[i], hash2[i] %= MOD;
	mana(s);
	// statics
	set<pair<LL, LL> > has;
	pair<LL, LL> c;
	int l = len << 1, L, R, k, m;
	for (int i = 0; i < tot; i++) {
		if ((i & 1) == 0) {
			k = d[i] >> 1, m = i - 1 >> 1;
			L = m - k, R = m + k;
			//cout << L << ' ' << R << endl;
			//cout << "mid " << i << ' ' << d[i] << endl;
			while (L <= R) {
				c = gethash(L, R);
				if (has.find(c) != has.end()) break;
				has.insert(c);
				L++, R--;
			}
		} else {
			k = d[i] >> 1, L = (i - 1 >> 1) - k, R = (i - 1 >> 1) + k - 1;
			//cout << L << ' ' << R << endl;
			//cout << "mid " << i << ' ' << d[i] << endl;
			while (L <= R) {
				c = gethash(L, R);
				if (has.find(c) != has.end()) break;
				has.insert(c);
				L++, R--;
			}
		}
	}
	return has.size();
}

bool check(char *s) {
	int l = 0, r = strlen(s) - 1;
	while (l < r && s[l] == s[r]) l++, r--;
	if (l < r) return 0;
	return 1;
}

int BF(char *s) {
	set<string> has;
	int r = strlen(s);
	while (r > 0) {
		s[r] = 0;
		for (int l = 0; l < r; l++) {
			if (check(s + l)) has.insert(s + l);
		}
		r--;
	}
	return has.size();
}

int main() {
	//freopen("in", "r", stdin);
	pre();
	int T, cas = 1, L = 5555;
	scanf("%d", &T);
	//T = 20;
	//srand(time(0));
	while (T--) {
		scanf("%s", str);
		//for (int i = 0; i < L; i++) str[i] = 'a' + rand() % 2;
		//str[L] = 0;
		int ans = work(str);
		printf("Case #%d: %d\n", cas++, ans);
		//int st = BF(str);
		//cout << st << endl;
		//if (st != ans) {
			//cout << st << ' ' << ans << endl;
			//while (1) ;
		//}
	}
	return 0;
}