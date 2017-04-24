#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <string>
#include <map>
using namespace std;

const int oo = 100000000;
int f[110][110];
map<string,int> ma;

int process(char *s)
{
	int ans = 0;
	for(int i = 0; s[i]; i ++) {
		if(isdigit(s[i])) {
			for(int j = i; s[j]; j ++) {
				if(isdigit(s[j])) ans = 10 * ans + (s[j] - '0');
			}
			break;
		}
	}
	return ans;
}

void update(int &x,int y)
{
	x = min(x,y);
}

int main()
{
	int cas = 0;
	char s[1100],ss[1100],str[1100];
	int n,m,r,a[2100];
	while(scanf("%d%d%d",&n,&m,&r) != EOF) {
		ma.clear();
		if(!n && !m && !r) break;
		scanf("%s",s);
		ma.clear();
		int cnt = 0;
		ma[s] = ++ cnt;
		int ct = 0;
		for(int i = 1; i <= m; i ++) {
			scanf("%s",s);
			if(!ma.count(s)) {
				ma[s] = ++ cnt;
			}
			a[++ ct] = ma[s];
			a[++ ct] = 1;
		}
		for(int i = 1; i <= 100; i ++) {
			for(int j = 1; j <= 100; j ++) {
				f[i][j] = oo;
			}
			f[i][i] = 0;
		}
		while(r --) {
			scanf("%s%s%s",s,ss,str);
			int x = process(ss);
			//cout << x << endl;
			if(!ma[s]) ma[s] = ++ cnt;
			if(!ma[str]) ma[str] = ++ cnt;
			if(ss[0] == '<') update(f[ma[s]][ma[str]],x);
			if(ss[strlen(ss) - 1] == '>') update(f[ma[str]][ma[s]],x);
		}
		for(int k = 1; k <= n; k ++)
			for(int i = 1; i <= n; i ++)
				for(int j = 1; j <= n; j ++)
					update(f[i][j],f[i][k] + f[k][j]);
		int pre = 1,ans = 0;
		for(int i = 1; i <= ct; i ++) {
			ans += f[pre][a[i]];
			//cout << pre << " " << a[i] << "   :   " << f[pre][a[i]] << endl;
			pre = a[i];
		}
		printf("%d. %d\n",++ cas,ans);
	}
	return 0;
}


		