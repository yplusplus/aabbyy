#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long get_sum(long long n)
{
	return n * n;
}

long long cal(long long n)
{
	if(!n) return 0;
	long long lt = 2,rt = n * 2,mid,ans = 2;
	while(lt <= rt) {
		mid = (lt + rt) >> 1;
		long long sum = 0;
		for(int j = 1; j <= 30; j ++) {
			int p = 1 << j;
			if(p > mid) break;
			long long tmp = mid >> j;
			sum += j * ((tmp + 1) >> 1);
			if(sum >= n) break;
		}
		if(sum < n) {
			lt = mid + 1;
		}
		else {
			ans = mid;
			rt = mid - 1;
		}
	}
	ans -= 2;
	long long tot = 0;
	long long sum = 0;
	for(int i = 1; i <= 30; i ++) {
		int p = 1 << i;
		if(p > ans) break;
		long long tmp = ans >> i;
		tot += i * ((tmp + 1) >> 1);
		sum += (long long)p * i * get_sum((tmp + 1) >> 1);
	}
	//cout << sum << " " << tot << endl;
	long long tt = ans + 2;
	ans += 2;
	long long mul = 1,cc = 0;
	while(ans % 2 == 0) ans >>= 1,mul *= 2,cc ++;
	cc = min(cc,n - tot);
	sum += cc * tt;
	return sum;
}

int main()
{
	long long n,m;
	while(scanf("%lld%lld",&n,&m) != EOF) {
		printf("%lld\n",cal(m) - cal(n - 1));
	}
	return 0;
}
