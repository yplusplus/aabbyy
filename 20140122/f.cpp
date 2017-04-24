#include <bits/stdc++.h>
using namespace std;

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
	y = tmp - (a / b) * y;
	return d;
}

long long a[15],n;

bool test1()
{
	int tot = 0;
	bool flag = false;
	for(int i = 1; i <= n; i ++)
		if(a[i]) {
			flag = true;
		}
		else tot ++;
	if(!flag) {
		printf("0\n");
		return true;
	}
	if(tot) return false;
	for(int i = 2; i <= n; i ++) {
		if(a[i] % a[i - 1]) return false;
		if(i > 2 && a[i] / a[i - 1] != a[i - 1] / a[i - 2]) return false;
	}
	printf("%lld\n",a[n] * (a[n] / a[n - 1]));
	return true;
}

bool test2()
{
	long long a1 = -1,a2 = -1;
	bool flag = false;
	for(int i = 2; i + 1 < n; i ++) {
		long long det = a[i - 1] * a[i + 1] - a[i] * a[i];
		if(det == 0) continue;
		long long x = a[i + 1] * a[i + 1] - a[i] * a[i + 2];
		if(x % det) continue;
		a1 = x / det;
		long long y =a[i - 1] * a[i + 2] - a[i + 1] * a[i];
		if(y % det) continue;
		a2 = y / det;
		flag = true;
		break;
	}
	if(flag == false) return false;
	for(int i = 3; i <= n; i ++) {
		if(a[i] != a2 * a[i - 1] + a1 * a[i - 2]) return false;
	}
	printf("%lld\n",a2 * a[n] + a1 * a[n - 1]);
	return true;
}

long long cal(long long a[4][4])
{
	return a[1][1] * (a[2][2] * a[3][3] - a[2][3] * a[3][2]) - a[1][2] * (a[2][1] * a[3][3] - a[2][3] * a[3][1])
		+ a[1][3] * (a[2][1] * a[3][2] - a[2][2] * a[3][1]);
}

void test3()
{
	long long a1,a2,a3;
	long long c[4][4],d[4][4];
	for(int i = 1; i + 5 <= n; i ++) {
		for(int j = 0; j < 3; j ++) {
			for(int k = 1; k <= 3; k ++) {
				c[j + 1][k] = a[i + j + k - 1];
			}
		}
		long long det = cal(c);
		if(det == 0) continue;
		for(int j = 1; j <= 3; j ++)
			for(int k = 1; k <= 3; k ++)
				d[j][k] = c[j][k];
		d[1][1] = a[i + 3],d[2][1] = a[i + 4],d[3][1] = a[i + 5];
		long long x = cal(d);
		if(x % det) continue;
		for(int j = 1; j <= 3; j ++)
			for(int k = 1; k <= 3; k ++)
				d[j][k] = c[j][k];
		d[1][2] = a[i + 3],d[2][2] = a[i + 4],d[3][2] = a[i + 5];
		long long y = cal(d);
		if(y % det) continue;
		for(int j = 1; j <= 3; j ++)
			for(int k = 1; k <= 3; k ++)
				d[j][k] = c[j][k];
		d[1][3] = a[i + 3],d[2][3] = a[i + 4],d[3][3] = a[i + 5];
		long long z = cal(d);
		if(z % det) continue;
		a1 = x / det;
		a2 = y / det;
		a3 = z / det;
	}
	printf("%lld\n",a1 * a[n - 2] + a2 * a[n - 1] + a3 * a[n]);
}
		
void solve()
{
	if(test1()) return;
	if(test2()) return;
	test3();
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t --) {
		scanf("%lld",&n);
		for(int i = 1; i <= n; i ++)
			scanf("%lld",&a[i]);
		solve();
	}
	return 0;
}
