#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int bit[N];
long long rmq[18][N];
long long a[N];

void init_rmq(int n)
{
	for(int i = 1;i <= n; i ++) rmq[0][i] = a[i];
	for(int j = 1; (1 << j) <= n; j ++)
		for(int i = 1;i <= n; i ++) {
			rmq[j][i] = rmq[j - 1][i];
			if(i + (1 << (j - 1)) <= n)
				rmq[j][i] = __gcd(rmq[j][i],rmq[j - 1][i + (1 << (j - 1))]);
		}
}

long long query_rmq(int lt,int rt)
{
	int len = bit[rt - lt + 1];
	return __gcd(rmq[len][lt],rmq[len][rt - (1 << len) + 1]);
}

void solve()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	init_rmq(n);
	long long ans = 0;
	for(long long i = 1; i <= n; i ++) {
		long long j = i;
		long long gcd = a[i];
		while(j <= n) {
			long long lt = j,rt = n,mid,pos;
			gcd = query_rmq(i,j);
			while(lt <= rt) {
				mid = (lt + rt) >> 1;
				if(query_rmq(i,mid) == gcd) pos = mid,lt = mid + 1;
				else rt = mid - 1;
			}
			ans = max(ans,gcd * (pos - i + 1));
			j = pos;
			if(j == n) break;
			long long new_gcd = __gcd(gcd,a[j + 1]);
			long long len = gcd / new_gcd * (j - i + 1);
			j = i + len - 1;
		}
	}
	cout << ans << endl;
}

int main()
{
	bit[0] = 0;
	bit[1] = 0;
	for(int i = 2; i < N; i ++) {
		int j = 0;
		for(; (1 << j) <= i; j ++);
		bit[i] = j - 1;
	}
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t --) solve();
	return 0;
}
