#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(i = a; i <= b; i ++)
typedef long long LL;
typedef pair<long long, long long> pll;

const int N = 111111;
const int BASE = 100010;
const pll MOD = pll(5800079, 7368787);
const pll KEY = pll(137, 104729);

pll operator%(pll a, pll b) { return pll(a.first % b.first, a.second % b.second); }
pll operator+(pll a, pll b) { return pll(a.first + b.first, a.second + b.second) % MOD; }
pll operator-(pll a, pll b) { return (pll(a.first - b.first, a.second - b.second) + MOD) % MOD; }
pll operator*(pll a, pll b) { return pll(a.first * b.first, a.second * b.second) % MOD; }
pll operator*(pll a, LL b) { return pll(a.first * b, a.second * b) % MOD; }

int slen, tlen;
pll sum[2][N];
pll KEY_fac[N];

char s[N],str[N],ss[N];
int nxt[N],ex[N];

bool equal(int a, int b, int c, int d) {
	a ++,b ++,c ++,d ++;
	pll tmp1 = (sum[0][b] - sum[0][a - 1] + MOD) % MOD;
	pll tmp2 = (sum[1][d] - sum[1][c - 1] + MOD) % MOD;
	tmp1 = tmp1 * KEY_fac[BASE - a] % MOD;
	tmp2 = tmp2 * KEY_fac[BASE - c] % MOD;
	return tmp1 == tmp2;
}

void ex_kmp()
{
	int lena = strlen(s);
	int lenb = strlen(str);
	nxt[0] = lenb,nxt[1] = lenb - 1;
	int i,j,k = 1,p,L;
	rep(i,0,lenb - 2) if(str[i] != str[i + 1]) {
		nxt[1] = i;
		break;
	}
	rep(i,2,lenb - 1) {
		p = k + nxt[k] - 1;
		L = nxt[i - k];
		if(i + L <= p) {
			nxt[i] = L;
		}
		else {
			j = p - i + 1;
			if(j < 0) j = 0;
			while(i + j < lenb && str[i + j] == str[j]) j ++;
			nxt[i] = j;
			k = i;
		}
	}
	int minlen = lena >= lenb ? lena : lenb;
	ex[0] = minlen;
	rep(i,0,minlen - 1) if(s[i] != str[i]) {
		ex[0] = i;
		break;
	}
	k = 0;
	rep(i,1,lena - 1) {
		p = k + ex[k] - 1,L = nxt[i - k];
		if(i + L <= p) {
			ex[i] = L;
		}
		else {
			j = p - i + 1;
			if(j < 0) j = 0;
			while(i + j < lena && j < lenb && s[i + j] == str[j]) j ++;
			ex[i] = j;
			k = i;
		}
	}
}

int ex1[N];
int n, m;
void init() {
	memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= n; i++) {
		sum[0][i] = (sum[0][i - 1] + KEY_fac[i] * (s[i] - 'a' + 1)) % MOD;
	}
	for (int i = 1; i <= m; i++) {
		sum[1][i] = (sum[1][i - 1] + KEY_fac[i] * (str[i] - 'a' + 1)) % MOD;
	}
}
int solve()
{
	n = strlen(s),m = strlen(str);
	if(n < m) return -1;
	ex_kmp();
	for(int i = 0; i < n; i ++) ex1[i] = ex[i];
	reverse(s,s + n);
	reverse(str,str + m);
	ex_kmp();
	reverse(s,s + n);
	reverse(str,str + m);
	for(int i = n; i >= 1; i --) s[i] = s[i - 1];
	for(int i = m; i >= 1; i --) str[i] = str[i - 1];
	init();
	for(int i = 0; i + m <= n; i ++) {
		if(ex1[i] == m) return i;
		int len1 = ex1[i];
		int len2 = ex[n - (i + m - 1) - 1];
		if(len1 + len2 + 2 >= m) return i;
		if(equal(i + len1 + 1,(i + m) - len2 - 2,len1 + 1,m - len2 - 2)) return i;
	}
	return -1;
}

int main()
{
	KEY_fac[0] = pll(1, 1);
	for (int i = 1; i < N; i++) {
		KEY_fac[i] = (KEY_fac[i - 1] * KEY) % MOD;
	}
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%s%s",s,str);
		printf("Case #%d: %d\n",cas,solve());
	}
	return 0;
}
