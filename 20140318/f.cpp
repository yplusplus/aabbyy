#include <bits/stdc++.h>
using namespace std;

map<string,int> ma;
map<int,string> rev;
bool dp[210][210],f[210][210];

struct point
{
	string s,str;
	point() {}
	point(string s,string str):s(s),str(str) {}
	friend bool operator < (const point &p,const point &q) {
		if(p.s != q.s) return p.s < q.s;
		return p.str < q.str;
	}
}a[210 * 210];

void solve(int n)
{
	ma.clear();
	string s,str;
	memset(dp,false,sizeof(dp));
	memset(f,false,sizeof(f));
	int tot = 0;
	while(n --) {
		cin >> s >> str;
		if(!ma.count(s)) {
			ma[s] = ++ tot;
			rev[tot] = s;
		}
		if(!ma.count(str)) {
			ma[str] = ++ tot;
			rev[tot] = str;
		}
		f[ma[s]][ma[str]] = dp[ma[s]][ma[str]] = true;
	}
	for(int k = 1; k <= tot; k ++)
		for(int i = 1; i <= tot; i ++)
			for(int j = 1; j <= tot; j ++)
				dp[i][j] |= (dp[i][k] & dp[k][j]);
	for(int k = 1; k <= tot; k ++)
		for(int i = 1; i <= tot; i ++)
			for(int j = 1; j <= tot; j ++)
				if(!dp[i][j]) continue;
				else if(dp[i][j] && dp[i][k] && dp[k][j] && k != i && k != j)
					dp[i][j] = false;
	int m = 0;
	for(int i = 1; i <= tot; i ++)
		for(int j = 1; j <= tot; j ++)
			if(!dp[i][j] && f[i][j]) {
				s = rev[i],str = rev[j];
				a[++ m] = point(s,str);
			}
	sort(a + 1,a + m + 1);
	cout << m;
	for(int i = 1; i <= m; i ++) {
		cout << " " << a[i].s << "," << a[i].str;
	}
	cout << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	int cas = 0;
    int n;	
	while(cin >> n, n) {
		cout << "Case " << ++ cas << ": ";
		solve(n);
	}
	return 0;
}
