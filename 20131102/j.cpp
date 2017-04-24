#include <bits/stdc++.h>
using namespace std;

long long cal(long long x,long long y,long long n)
{
	if(x == y) return n / x;
	if(n < x) return 0;
	if(x == 1) return n;
	if(n <= y) return n - x + 1;
	if(y >= 2 * x) return n - x + 1;
	long long d = y - x;
	long long times = (x - 1) / d;
	long long tt = n / x;
	if(times >= tt) {
		long long ans = (tt - 1) + (tt - 1) * tt * d / 2;
		long long left = n % x;
		return ans + min(left + 1,tt * d + 1);
	}
	else {
		long long ans = times + times * (times + 1) * d / 2;
		long long left = n - x * (times + 1) + 1;
		return ans + left;
	}
}

int main()
{
//	cout << cal(4,6,13) << endl;
	long long x,y,n,m;
	cin >> x >> y >> n >> m;
	cout << cal(x,y,m) - cal(x,y,n - 1) << endl;
	return 0;
}
