#include <bits/stdc++.h>
using namespace std;

int main()
{
	long long f[10010],g[10010];
	long long n,m;
	ios::sync_with_stdio(0);
	while(cin >> n >> m) {
		if(!n && !m) break;
		f[1] = g[1] = 1 % m;
		f[2] = g[2] = 2 % m;
		for(int i = 3; i <= n; i ++) {
			f[i] = (f[i- 1] + f[i - 1] * g[i - 1]) % m;
			g[i] = (3 * g[i - 1] + g[i - 2] * g[i - 2] - g[i - 1] * g[i - 1]) % m;
		}
		if(f[n] < 0) f[n] += m;
		cout << f[n] << endl;
	}
	return 0;
}
