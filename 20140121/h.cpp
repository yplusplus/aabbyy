#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	int id;
	long long r,c,p;
	cin >> t;
	while(t --) {
		cin >> id >> p >> r >> c;
		long long ans = 1;
		cout << id << " ";
		long long cc = min(c,r - c);
		for(long long i = 1; i <= cc; i ++) {
			long long d = __gcd(ans,i);
			long long ii = i / d;
			long long dd = __gcd(r - i + 1,ii);
			ii /= dd;
			ans /= d;
			ans = ans * ((r - i + 1) / dd) / ii;
		}
		for(int i = 1; i <= r - c; i ++)
			ans *= p;
		cout << ans << endl;
	}
	return 0;
}
	
