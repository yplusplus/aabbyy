#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("army.in","r",stdin);
	ios::sync_with_stdio(0);
	int t;
	long long n;
	cin >> t;
	for(int cas = 1; cas <= t; cas ++) {
		cin >> n;
		unsigned long long lt = 1,rt = 2000000,mid,K = 1;
		while(lt <= rt) {
			mid = (lt + rt) >> 1;
			if(mid * (mid + 1) * (2 * mid + 1) / 6 >= n) {
				K = mid;
				rt = mid - 1;
			}
			else lt = mid + 1;
		}
		n -= (K - 1) * K * (2 * K - 1) / 6;
		lt = 1,rt = 2 * K - 1,mid;
		unsigned long long ans = 0;
		while(lt <= rt) {
			mid = (lt + rt) >> 1;
			unsigned long long sum = 0;
			if(mid <= K) sum = mid * (mid + 1) / 2;
			else {
				sum = K * (K + 1) / 2;
				unsigned long long i = mid - K;
				sum += K * i - i * (i + 1) / 2;
			}
			if(sum >= n) {
				ans = mid;
				rt = mid - 1;
			}
			else lt = mid + 1;
		}
		ans += (K - 1) * (K - 1);
		cout << "Case " << cas << ": " << ans << endl;
	}
	return 0;
}
