#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("money.in","r",stdin);
	freopen("money.out","w",stdout);
	long long n;
	cin >> n;
	n ++;
	for(long long i = 1; i * i <= n; i ++) {
		if(n % i) continue;
		long long x = i + 1,y = n / i + 1;
		if(__gcd(x,y) == 1) {
			cout << x << " " << y << endl;
			return 0;
		}
	}
	cout << "0 0" << endl;
	return 0;
}
