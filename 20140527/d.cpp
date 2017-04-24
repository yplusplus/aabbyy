#include <bits/stdc++.h>
using namespace std;

const int mod = 100000;
const int SIZE = 40;
const int N = 110;
struct bignum
{
	int a[SIZE];
	bignum() {
		memset(a,0,sizeof(a));
	}

	void adjust() {
		for(int i = 0; i < SIZE; i ++)
			if(a[i] >= mod) {
				a[i + 1] += a[i] / mod;
				a[i] %= mod;
			}
	}

	bignum operator + (const bignum &p) {
		bignum c;
		for(int i = 0; i < SIZE; i ++) c.a[i] = a[i] + p.a[i];
		c.adjust();
		return c;
	}

	bignum operator * (int x) {
		bignum c;
		for(int i = 0; i < SIZE; i ++) c.a[i] = a[i] * x;
		c.adjust();
		return c;
	}

	bignum operator - (bignum &p) {
		bignum c;
		for(int i = 0; i < SIZE; i ++) c.a[i] = a[i] - p.a[i];
		for(int i = 0; i < SIZE; i ++)
			if(c.a[i] < 0) {
				c.a[i] += mod;
				c.a[i + 1] --;
			}
		return c;
	}

	void output() {
		int i;
		for(i = SIZE - 1; i >= 0; i --)
			if(a[i]) break;
		if(i == -1) i ++;
		printf("%d",a[i]);
		for(i = i - 1; i >= 0; i --) printf("%05d",a[i]);
		printf("\n");
	}
}S[N][N],f[N];

bignum dp[1 << 10];
int pre[N];
int find(int x)
{
	if(pre[x] == -1) return x;
	return pre[x] = find(pre[x]);
}

vector<int> v[N];
int main()
{
	freopen("partitions.in","r",stdin);
	freopen("partitions.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	int tm = 0;
	for(int i = 0; i < m; i ++) {
		int x,y;
		scanf("%d",&x);
		if(!x) continue;
		while(x --) {
			scanf("%d",&y);
			v[tm].push_back(y);
		}
		tm ++;
	}
	m = tm;
	S[0][0].a[0] = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= i; j ++)
			S[i][j] = (S[i - 1][j] * j) + S[i - 1][j - 1];
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= i; j ++)
			f[i] = f[i] + S[i][j];
	for(int i = 0; i < (1 << m); i ++) {
		memset(pre,-1,sizeof(pre));
		for(int j = 0; j < m; j ++) {
			if(!(i & (1 << j))) continue;
			for(int k = 1; k < v[j].size(); k ++) {
				int x = find(v[j][k - 1]);
				int y = find(v[j][k]);
				if(x != y) pre[x] = y;
			}
		}
		int tot = 0;
		for(int j = 1; j <= n; j ++)
			if(pre[j] == -1) tot ++;
		dp[i] = f[tot];
	}
	for(int i = (1 << m); i >= 0; i --) {
		int mask = ((1 << m) - 1) ^ i;
		for(int j = mask; j; j = (j - 1) & mask)
			dp[i] = dp[i] - dp[i ^ j];
	}
	dp[0].output();
	return 0;
}
