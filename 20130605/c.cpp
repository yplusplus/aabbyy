#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int cal(int n,int x)
{
	if(n == 0) return 0;
	n ++;
	int times = n / (1 << (x + 1));
	int ans = times * (1 << x);
	n %= (1 << (x + 1));
	if(n > (1 << x)) ans += (n - (1 << x));
	return ans;
}

int main()
{
	int a,b;
	while(scanf("%d%d",&a,&b) != EOF) {
		if(b == 0 || a == b) {
			printf("0\n");
			continue;
		}
		long long ans = 0,pre = 0;
		if(a == 0) a ++;
		for(int i = 0; i < 510; i ++) {
			long long cc = 0;
			if(i < 30) cc = cal(b,i) - cal(a - 1,i);
			cc += pre;
			ans += cc / 2;
			pre = cc / 2;
		}
		cout << ans << endl;
	}
	return 0;
}

