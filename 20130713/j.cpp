#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

bool prime(int n)
{
	for(int i = 2; i * i <= n; i ++)
		if(n % i == 0) return false;
	return true;
}

int pri[110],cc;
int sum,root;

void cal(int x,int pos,int step)
{
	if(step & 1) sum += root / x;
	else sum -= root / x;
	if(pos > cc) return;
	for(int i = pos; i <= cc; i ++) {
		if(1LL * x * pri[i] <= root)
			cal(x * pri[i],i + 1,step + 1);
	}
}

	
int main()
{
	int a,b,n;
	scanf("%d%d%d",&a,&b,&n);
	++ n;
	cc = 0;
	for(int i = 2; i <= n; i ++)
		if(prime(i)) pri[++ cc] = i;
	reverse(pri + 1,pri + cc + 1);
	root = a;
	sum = 0;
	cal(1,1,1);
	long long ans = -sum;
	root = a + b;
	sum = 0;
	cal(1,1,1);
	ans += sum;
	for(int i = 1; i <= cc; i ++)
		if(pri[i] >= a + 1 && pri[i] <= a + b) ans ++;
	cout << ans << endl;
	/*
	ans = 0;
	for(int i = a + 1; i <= a + b; i ++) {
		bool flag = true;
		for(int j = 2; j <= n; j ++) {
			if(i % j == 0) {
				flag = false;
				break;
			}
		}
		if(flag) ans ++;
	}
	cout << ans << endl;*/
	return 0;
}


