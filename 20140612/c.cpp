#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int main()
{
	freopen("budget.in","r",stdin);
	freopen("budget.out","w",stdout);
	long long m,n,p;
	long long a[N],b[N];
	cin >> m >> n >> p;
	for(int i = 1; i <= m; i ++) {
		cin >> a[i];
	}
	for(int i = 1; i <= n; i ++) cin >> b[i];
	sort(a + 1,a + m + 1);
	sort(b + 1,b + n + 1);
	int visit[N];
	long long ans = 0;
	long long lt = 0,rt = 200000000000000LL,mid;
	while(lt <= rt) {
		mid = (lt + rt) >> 1;
		memset(visit,0,sizeof(visit));
		for(int i = 1; i <= m; i ++) {
			long long now = mid;
			for(int j = n; j >= 1; j --) {
				if(!visit[j]) {
					long long val = p % a[i] == 0 ? p / a[i] : p / a[i] + 1;
					if(b[j] + val - 1 <= now) {
						visit[j] = 1;
						now -= val;
					}
					//if(max(now,b[j]) + val - 1 <= mid) now = max(now,b[j]) + val,visit[j] = 1;
				}
			}
		}
		bool flag = true;
		for(int i = 1; i <= n; i ++) flag &= visit[i];
		if(flag) ans = mid,rt = mid - 1;
		else lt = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
