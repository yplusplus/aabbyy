#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 50010;
int c[50010],re[50010],ans[50010],nxt[50010];
int visit[50010];

int main()
{
	int n,m,p,a,b;
	while(scanf("%d%d%d%d%d",&n,&m,&p,&a,&b) != EOF) {
		int tmp = n / m;
		int left = n - tmp;
		int cc = 0;
		for(int i = 1; i <= left; i ++) re[++ cc] = i + tmp;
		int pos = 1;
		int cnt = 0;
		for(int i = 1; i <= tmp; i ++) {
			int l = m - 1;
			while(l -- && pos <= cc) c[++ cnt] = re[pos ++];
			c[++ cnt] = i;
		}
		while(pos <= cc) c[++ cnt] = re[pos ++];
//		for(int i = 1; i <= n; i ++)
//			cout << c[i] << " ";
//		cout << endl;
		for(int i = 1; i <= n; i ++)
			nxt[i] = c[i];
		/*
		for(int i = 1; i <= n; i ++)
			cout << nxt[i] << " ";
		cout << endl;
		*/
		memset(visit,0,sizeof(visit));
		for(int i = 1; i <= n; i ++) {
			if(visit[i]) continue;
			int tmp = i;
			cc = 0;
			while(!visit[tmp]) {
				visit[tmp] = 1;
				c[cc ++] = tmp;
				tmp = nxt[tmp];
			}
			/*
			for(int i = 0; i < cc; i ++)
				cout << c[i] << " ";
			cout << endl;
			*/
			for(int j = 0; j < cc; j ++)
				ans[c[j]] = c[(j + p) % cc];
		}
		for(int i = a; i <= b; i ++) {
			printf("%d",ans[i]);
			if(i == b) printf("\n");
			else printf(" ");
		}
	}
	return 0;
}
