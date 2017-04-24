#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
bool check(int n)
{
	for(int i = 2; i * i <= n; i ++)
		if(n % i == 0) return false;
	return true;
}

char s[N];
int fac[55];
int ct = 0;
int lt[55];
int p[25][N];
int a[N];

int get_mod(int mod,int n)
{
	int ans = 0;
	for(int i = 0; i < n; i ++)
		ans = (ans * 10 + (s[i] - '0')) % mod;
	return ans;
}

long long x,y;
long long ex_gcd(long long a,long long b)
{
	if(!b) {
		x = 1, y = 0;
		return a;
	}
	long long d = ex_gcd(b,a % b);
	long long tmp = x;
	x = y;
	 y = tmp - (a / b) * y;
	 return d;
}

long long ival(long long p,long long q)
{
	p %= q;
	if(p <= 0) p += q;
	return p;
}

long long solve(long long a[],long long b[],long long m)
{
	long long ans = b[0],lcm = a[0];
	if(!b[0]) ans = a[0];
	for(int i = 1; i < m; i ++) {
		long long d = ex_gcd(lcm,a[i]);
		if((b[i] - ans) % d) return -1;
		x *= ((b[i] - ans) / d);
		x = ival(x,a[i] / d);
		ans = ival(ans + lcm * x,lcm / d * a[i]);
		lcm = lcm / d * a[i];
	}
	return ans;
}

void get_ans(long long mod)
{
	if(mod == 1) {
		printf("0\n");
		return;
	}
	bool flag = false;
	int cnt = 0;
	long long a[20],b[20];
	for(int i = 0; i < ct; i ++) {
		if(mod % fac[i] == 0) {
			a[cnt] = fac[i];
			b[cnt] = lt[i];
			cnt ++;
			if(lt[i]) flag = true;
		}
	}
	if(!flag) {
		printf("0\n");
		return;
	}
	printf("%I64d\n",solve(a,b,cnt));
}

int main()
{
	for(int i = 2; i <= 47; i ++)
		if(check(i)) fac[ct ++] = i;
	scanf("%s",s);
	int n = strlen(s);
	//reverse(s,s + n);
	for(int i = 0; i < n; i ++) a[i] = s[i] - '0';
	for(int i = 0; i < ct; i ++) {
		lt[i] = get_mod(fac[i],n);
	}
//	cout << "yes" << lt[3] << endl;
	for(int i = 0; i < ct; i ++) {
		p[i][0] = 1;
		for(int j = 1; j < N; j ++) {
			p[i][j] = p[i][j - 1] * 10 % fac[i];
		}
	}
	//cout << fac[0] << " " << fac[1] << endl;
	long long cd,x,y;
	int m;
	scanf("%d",&m);
	while(m --) {
		scanf("%I64d%I64d",&cd,&x);
		if(cd == 1) {
			x = n - x;
			scanf("%I64d",&y);
			for(int i = 0; i < ct; i ++) {
				lt[i] = (lt[i] - p[i][n - 1 - x] * a[x] + y * p[i][n - 1 - x]) % fac[i];
				if(lt[i] < 0) lt[i] += fac[i];
	//			if(i == 1) {
	//				cout << p[i][n - 1 - x] << " " << a[x] << " " << y << " " << lt[i] << endl;
	//			}
			}
			a[x] = y;
		}
		else {
	//		cout << "omg " << lt[0] << " " << lt[1] << endl;
			get_ans(x);
		}
	}
	return 0;
}
