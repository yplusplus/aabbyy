#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int N = 100010;
long long a[N],b[N];

long long cal(long long n)
{
	long long inv2 = (mod + 1) >> 1;
	return n % mod * (n + 1) % mod * inv2 % mod;
}

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin >> n;
	long long sum = 0,tot = 0;
	for(int i = 1; i <= n; i ++) {
		cin >> a[i] >> b[i];
		sum += 1LL * a[i] * b[i];
		tot += a[i];
	}
	long long avg = sum / tot;
	long long ans = 0;
	long long has = 0;
	for(int i = 1; i <= n; i ++) {
		if(has == 0) {
			if(b[i] == avg) continue;
			if(b[i] > avg) {
				has = a[i] * (b[i] - avg);
				ans = (ans + (b[i] - avg) * cal(a[i] - 1) % mod) % mod;
			}
			else if(b[i] < avg) {
				has = a[i] * (b[i] - avg);
				ans = (ans + cal(a[i]) * (avg - b[i]) % mod) % mod;
			}
		}
		else if(has > 0) {
			if(b[i] == avg) {
				ans = (ans + a[i] * (has % mod)) % mod;
			}
			else if(b[i] > avg) {
				ans = (ans + a[i] * (has % mod)) % mod;
				ans = (ans + cal(a[i] - 1) * (b[i] - avg)) % mod;
				has += a[i] * (b[i] - avg);
			}
			else {
				long long need = (avg - b[i]) * a[i];
				if(has >= need) {
					has -= need;
					ans = (ans + a[i] * (has % mod)) % mod;
					ans = (ans + cal(a[i]) * (avg - b[i])) % mod;
				}
				else {
					long long tmp = has;
					long long dis = has / (avg - b[i]);
					ans = (ans + cal(dis) * (avg - b[i])) % mod;
					has -= dis * (avg - b[i]);
					ans = (ans + (dis + 1) * has) % mod;
					ans = (ans + cal((a[i] - dis - 1)) * (avg - b[i])) % mod;
					ans = (ans + (a[i] - dis) * (avg - b[i] - has) % mod) % mod;
					has = tmp - need;
				}
			}
		}
		else {
			if(b[i] == avg) {
				ans = (ans + a[i] * (abs(has) % mod)) % mod;
			}
			else if(b[i] > avg) {
				long long maxn = (b[i] - avg) * a[i];
				if(maxn >= -has) {
					long long dis = abs(has) / (b[i] - avg);
					ans = (ans + cal(dis - 1) * (b[i] - avg)) % mod;
					ans = (ans + dis * (-has - dis * (b[i] - avg))) % mod;
					if(dis + 2 <= a[i]) ans = (ans + cal(a[i] - dis - 2) * (b[i] - avg)) % mod;
					if(dis + 1 <= a[i]) ans = (ans + (b[i] - avg - (-has - dis * (b[i] - avg))) * (a[i] - dis - 1)) % mod;
					has = maxn + has;
				}
				else {
					ans = (ans + cal(a[i] - 1) * (b[i] - avg)) % mod;
					ans = (ans + ((-has - maxn) % mod) * a[i]) % mod;
					has += maxn;
				}
			}
			else {
				ans = (ans + a[i] * (abs(has) % mod)) % mod;
				ans = (ans + cal(a[i]) * (avg - b[i])) % mod;
				has -= (avg - b[i]) * a[i];
			}
		}		
	}
	ans = (ans % mod + mod) % mod;
	cout << ans << endl;
	return 0;
}
