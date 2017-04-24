#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;

map<long long,int> ma;

long long pow(long long a,long long b,long long c)
{
	long long ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % c;
		a = a * a % c;
		b /= 2;
	}
	return ans;
}

int fac[55],cnt;

long long factor(long long n)
{
	cnt = 0;
	for(int i = 2; i * i <= n; i ++) {
		if(n % i) continue;
		while(n % i == 0) n /= i;
		fac[cnt ++] = i;
	}
	if(n > 1) fac[cnt ++] = n;
}

bool check(int x,int n)
{
	for(int i = 0; i < cnt; i ++)
		if(pow(x,n / fac[i],n + 1) == 1) return false;
	return true;
}

long long proot(long long n)
{
	factor(n - 1);
	for(int i = 1; ; i ++)
		if(check(i,n - 1)) return i;
}

//find x, a ^ x = b(mod n)
//m = cell(sqrt(n))
//x = i * m + j
//a ^ (-mi) * b = a ^ j
long long babystep_giantstep(long long a,long long b,long long n)
{
	long long m = ceil(sqrt(n * 1.0));
	long long x = 1;
	ma.clear();
	for(int i = 0; i < m; i ++) {
		ma[x] = i;
		x = x * a % n;
	}
	long long y = x;
	x = 1;
	for(int i = 0; ; i ++) {
		long long tmp = pow(x,n - 2,n) * b % n;
		if(ma.count(tmp)) {
			return i * m + ma[tmp];
		}
		x = x * y % n;
	}
	while(1) {
		cout << "omg\n";
	}
}

long long x,y;
long long ex_gcd(long long a,long long b)
{
	if(!b) {
		x = 1,y = 0;
		return a;
	}
	long long d = ex_gcd(b,a % b);
	long long tmp = x;
	x = y;
	y = tmp - a / b * y;
	return d;
}

long long ans[1000010];
//x ^ K = A(mod P)
//A = root ^ j
//x = root ^ i
//root ^ (i * k) = root^(j) (mod P)
//root ^ (P - 1) = 1 (mod P)
//i * k = j(mod (P - 1))
int main()
{
	long long A,K,P;
	ios::sync_with_stdio(false);
	while(cin >> P >> K >> A) {
		if(!A) {
			cout << 1 << endl;
			cout << 0 << endl;
			continue;
		}
		long long root = proot(P);
		long long j = babystep_giantstep(root,A,P);
		long long d = ex_gcd(K,P - 1);
	//	printf("%lld %lld %lld\n",root,j,d);
		if(j % d) {
			cout << 0 << endl;
			continue;
		}
		x = x % (P - 1) * (j / d) % (P - 1);
		x = (x % (P - 1) + (P - 1)) % (P - 1);
		int cnt = 1;
		ans[0] = x % ((P - 1) / d);
		for(int i = 1; i < d; i ++) {
			ans[cnt ++] = (ans[cnt - 1] + (P - 1) / d) % (P - 1);
		}
		for(int i = 0; i < cnt; i ++)
			ans[i] = pow(root,ans[i],P);
		sort(ans,ans + cnt);
		cout << cnt << endl;
		for(int i = 0; i < cnt; i ++) {
			cout << ans[i];
			if(i == cnt - 1) cout << endl;
			else cout << " ";
		}
	}
	return 0;
}




