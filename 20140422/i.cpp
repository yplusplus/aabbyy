#include <bits/stdc++.h>
using namespace std;

long long mod;
long long add(long long a,long long b,long long mod)
{
	return (a + b) % mod;
}

long long mul(long long a,long long b,long long mod)
{
	if(a < b) swap(a,b);
	long long ans = 0;
	while(b) {
		if(b & 1LL) ans = (ans + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return ans;
}

struct matrix
{
	long long a[7][7];
	matrix() {
		memset(a,0,sizeof(a));
	}
	matrix operator * (const matrix &p) {
		matrix c;
		for(int i = 0; i < 7; i ++)
			for(int j = 0; j < 7; j ++)
					for(int k = 0; k < 7; k ++) {
						c.a[i][j] = add(c.a[i][j],mul(a[i][k],p.a[k][j],mod),mod);
					}
		return c;
	}
};

matrix pow(long long n,matrix t)
{
	if(n == 1) return t;
	if(n & 1LL) return pow(n >> 1,t * t) * t;
	return pow(n >> 1,t * t);
}

int maps[15][15];
matrix init(long long cr)
{
	matrix a;
	for(int i = 0; i < 3; i ++)
		for(int j = 0; j < 3; j ++) {
			if(maps[i][j] == -1) continue;
			for(int k = 0; k < 3; k ++) {
				if(maps[j][k] == -1) continue;
				if(i != 2 && i == k) continue;
				if(i != 2) a.a[maps[i][j]][maps[j][k]] = 1 % mod;
				else {
					int tot = (j == 2 ? 1 : 0) + (k == 2 ? 1 : 0);
					if(tot + 2 < cr) {
						a.a[maps[i][j]][maps[j][k]] = (cr - tot - 2) % mod;
					}
				}
			}
		}
	return a;
}

const int N = 90010;
int pri[N],fac[N],num[N],cnt;

void prime()
{
	int a[N];
	memset(a,0,sizeof(a));
	for(int i = 2; i * i < N; i ++)
		if(!a[i])
			for(int j = i * i; j < N; j += i)
				a[j] = 1;
	for(int i = 0, j = 2; j < N; j ++)
		if(!a[j]) pri[i ++] = j;
}

void factor(int n)
{
	cnt = 0;
	for(int i = 0; pri[i] * pri[i] <= n; i ++) {
		if(n % pri[i]) continue;
		while(n % pri[i] == 0) n /= pri[i];
		fac[cnt ++] = pri[i];
	}
	if(n > 1) fac[cnt ++] = n;
}

int get_phi(int n)
{
	long long ans = n;
	for(int i = 0; i < cnt; i ++)
		if(n % fac[i]) continue;
		else ans = ans / fac[i] * (fac[i] - 1);
	return ans;
}

int main()
{
	memset(maps,-1,sizeof(maps));
	int tot = 0;
	for(int i = 0; i < 3; i ++)
		for(int j = 0; j < 3; j ++)
			if(i == j && i != 2) continue;
			else maps[i][j] = tot ++;
	//for(int i = 0; i < 3; i ++) for(int j = 0; j < 3; j ++) if(maps[i][j] != -1) cout << i << " " << j << " : " << maps[i][j] << endl;
	prime();
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		long long n,m,r;
		cin >> n >> r >> m;
		if(r < 3) {
			printf("Case %d: %d\n",cas,0);
			continue;
		}
		factor(n);
		mod = n * m;
		matrix a = init(r);
		//for(int i = 0; i < 7; i ++) { for(int j = 0; j < 7; j ++) cout << a.a[i][j] << " "; cout << endl; }
		long long ans = 0;
		for(int i = 1; i * i <= n; i ++) {
			if(n % i) continue;
			long long len = n / i,phi = get_phi(i);
			if(len >= 3) {
				long long tmp = 0;
				matrix b = pow(len - 2,a);
				//cout << endl;
				//for(int j = 0; j < tot; j ++) { for(int k = 0; k < tot; k ++) cout << a.a[j][k] << " "; cout << endl; }
				for(int j = 0; j < 3; j ++)
					for(int k = 0; k < 3; k ++)
						if(maps[j][k] == -1) continue;
						else {
							if(len == 3 && j == 2 && k == 1) tmp += mul(b.a[maps[j][k]][2],r * (r - 1),mod);
							else if(len > 3) {
								if(k != 0 && j == 2) {
									tmp += mul(b.a[maps[j][k]][2],r * (r - 1),mod);
								}
							}
							tmp %= mod;
						}
				ans = (ans + mul(phi,tmp,mod)) % mod;
			}
			if(i * i == n) break;
			len = i,phi = get_phi(n / i);
			if(len >= 3) {
				long long tmp = 0;
				matrix b = pow(len - 2,a);
				for(int j = 0; j < 3; j ++)
					for(int k = 0; k < 3; k ++)
						if(maps[j][k] == -1) continue;
						else {
							if(len == 3 && j == 2 && k == 1) tmp += mul(b.a[maps[j][k]][2],r * (r - 1),mod);
							else if(len > 3) {
								if(k != 0 && j == 2) tmp += mul(b.a[maps[j][k]][2],r * (r - 1),mod);
							}
							tmp %= mod;
						}
				ans = (ans + mul(phi,tmp,mod)) % mod;
//				cout << tmp << endl;
			}
		}
		printf("Case %d: %lld\n",cas,ans / n);

	}
	return 0;
}
