#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const long long oo = 1LL << 60;
long long mod;
map<unsigned long long,bool> ma;
struct matrix
{
	unsigned long long a[2][2];
	matrix() {
		memset(a,0,sizeof(a));
	}
	matrix operator * (matrix &p) {
		matrix c;
		for(int i = 0; i < 2; i ++)
			for(int j = 0; j < 2; j ++)
				for(int k = 0; k < 2; k ++)
					c.a[i][j] = (c.a[i][j] + a[i][k] * p.a[k][j]) % mod;
		return c;
	}
};

matrix pow(matrix t,long long n)
{
	if(n == 1) return t;
	if(n & 1LL) return pow(t * t,n / 2) * t;
	return pow(t * t,n / 2);
}

bool cmp(matrix a)
{
	return a.a[0][0] == 1 && a.a[1][1] == 1 && !a.a[0][1] && !a.a[1][0];
}

bool sure(long long n)
{
	if(ma.count(n)) return ma[n];
	matrix a;
	a.a[0][0] = a.a[0][1] = a.a[1][0] = 1;
	/*
	if(n == 18) {
		matrix b = pow(a,n);
		cout << b.a[0][0] << " " << b.a[0][1] << " " << b.a[1][0] << " " << b.a[1][1] << endl;
	}
	*/
	return ma[n] = cmp(pow(a,n));
}

long long cal(long long n)
{
	long long i;
	for(i = 1; i * i <= n; i ++) {
		if(n % i) continue;
		if(i > 1 && sure(i)) return i;
	}
	for(i; i >= 1; i --) {
		if(n % i) continue;
	//	cout << n << " " << n / i << endl;
		if(sure(n / i)) return n / i;
	}
	return oo;
}


long long cal_period(long long n)
{
	mod = n;
	if(n == 2) return 3;
	if(n == 3) return 8;
	if(n == 5) return 20;
	ma.clear();
	return min(cal(2 * n + 2),cal(n - 1));
}

long long find(long long n)
{
	long long ans = 1;
	for(long long i = 2; i * i <= n; i ++) {
		if(n % i) continue;
		n /= i;
		long long x = cal_period(i);
		while(n % i == 0) n /= i,x *= i;
		ans = ans / __gcd(x,ans) * x;
	}
	if(n > 1) {
		long long x = cal_period(n);
		ans = ans / __gcd(x,ans) * x;
	}
	return ans;
}

int main()
{
	long long n;
	while(cin >> n) {
		if(n == 2) {
			cout << 3 << endl;
			continue;
		}
		if(n == 3) {
			cout << 4 << endl;
			continue;
		}
		if(n == 5) {
			cout << 10 << endl;
			continue;
		}
		cout << find(n) / 2 << endl;
	/*
		matrix a;
		a.a[0][0] = a.a[0][1] = a.a[1][0] = 1;
		a.a[1][1] = 2;
		for(int i = 2; ; i ++) {
			mod = n;
			if(cmp(pow(a,i))) {
				cout << i << endl;
				break;
			}
		}
	*/	
	}
	return 0;
}
