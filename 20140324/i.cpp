#include <bits/stdc++.h>
using namespace std;

const int LCM = 13 * 11 * 7 * 5 * 9 * 8;
bool dp[LCM + 10];
set<int> st;


void init()
{
	dp[0] = 1;
	for(int i = 1; i < 13; i ++)
		for(int j = i + 1; j <= 13; j ++) {
			int x = LCM / j * i;
			for(int k = LCM; k >= x; k --)
				dp[k] |= dp[k - x];
		}
	for(int i = 0; i <= LCM; i ++)
		if(dp[i]) st.insert(i);
}


int main()
{
	freopen("zanzibar.in","r",stdin);
	ios::sync_with_stdio(false);
	init();
	int t;
	cin >> t;
	for(int cas = 1; cas <= t; cas ++) {
		long long X,Y;
		cin >> X >> Y;
//		cout << X << " " << Y << " " << Y * LCM << " " << LCM << endl;
		long long ltt = 0,rtt = LCM * Y,mid,ans = X * LCM;
		while(ltt <= rtt) {
			mid = (ltt + rtt) >> 1;
			long long rt = (X * LCM + mid) / Y;
			long long lt = X * LCM - mid;
			if(lt < 0) lt = 0;
			else lt = lt % Y == 0 ? lt / Y : lt / Y + 1;
			bool flag = false;
			set<int>::iterator it = st.lower_bound(lt);
			if(it != st.end() && (*it) <= rt) flag = true;
			if(flag) ans = mid,rtt = mid - 1;
			else ltt = mid + 1;
		}
//		ans = abs(ans * Y - X * LCM);
//		cout << ans << " " << Y * LCM << endl;
		long long d = __gcd(ans,Y * LCM);
		cout << "Case " << cas << ": " << ans / d << "/" << Y * LCM / d << endl;
	}
	return 0;
}

