#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1200010;
long long pri[N];
bool a[N];

void prime()
{
	memset(a,false,sizeof(a));
	for(int i = 2; i * i < N; i ++)
		if(!a[i])
			for(int j = i * i; j < N; j += i)
				a[j] = 1;
	for(int i = 0, j = 2; j < N; j ++)
		if(!a[j]) pri[i ++] = j;
}

long long fac[N];
int cnt;
void factor(long long n)
{
	cnt = 0;
	for(int i = 0; pri[i] * pri[i] <= n; i ++) {
		if(n % pri[i]) continue;
		while(n % pri[i] == 0) n /= pri[i];
		fac[cnt ++] = pri[i];
	}
	if(n > 1) fac[cnt ++] = n;
}

long long cal(long long n)
{
	long long ans = 0;
	for(int i = 0; i < (1 << cnt); i ++) {
		long long tmp = 1;
		int cc = 0;
		for(int j = 0; j < cnt; j ++)
			if(i & (1 << j)) tmp = tmp * fac[j],cc ++;
		if(cc & 1) ans -= n / tmp;
		else ans += n / tmp;
	}
	return n - ans;
}

int main()
{
	long long a,n;
	prime();
	cin >> a >> n;
	factor(a);
	if(n == 1) {
		if(a & 1LL) {
			cout << 1 << endl;
			return 0;
		}
		cout << 0 << endl;
		return 0;
	}
	if(a == 1) {
		n = (n + 1) / 2;
		cout << n << endl;
		return 0;
	}
	factor(a);
	if(a % 2 == 0) {
		cout << cal(n) << endl;
		return 0;
	}
	else {
		cout << (n + 1) / 2 + cal(n / 2) << endl;
		return 0;
	}
	return 0;
}

