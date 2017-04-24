#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
int Map[N];
vector<int> vv[N],v[N],mat[N];
int size[N],cc,C[N];

void dummy(int n,vector<int> a)
{
	++ cc;
	//cout << cc << endl;
	for(int i = 0; i < n; i ++) {
		Map[a[i]] = cc;
		C[a[i]] ++;
		vv[cc].push_back(a[i]);
	}
	size[cc] = n;
}

vector<int> a;
void search(int n,vector<int> mat[],int *dfn,int *low,int now,int &cnt,int *st,int &sp)
{
	int i,m;
	dfn[st[sp ++] = now] = low[now] = ++ cnt;
	for(int j = 0; j < mat[now].size(); j ++) {
		i = mat[now][j];
		if(!dfn[i]) {
			search(n,mat,dfn,low,i,cnt,st,sp);
			if(low[i] < low[now]) low[now] = low[i];
			if(low[i] >= dfn[now]) {
				a.clear();
				for(st[sp] = -1,a.push_back(now),m = 1; st[sp] != i; a.push_back(st[-- sp]), m ++);
				dummy(m,a);
			}
		}
		else if(dfn[i] < low[now]) low[now] = dfn[i];
	}
}

int dfn[N],low[N],st[N],visit[N];

void block(int n,vector<int> mat[])
{
	int i,cnt,sp = 0;
	for(i = 0; i < n; dfn[i ++] = 0);
	for(cnt = i = 0; i < n; i ++)
		if(!dfn[i]) search(n,mat,dfn,low,i,cnt,st,sp);
}

int ind[N];
int main()
{
	int cas = 0;
	int m,n,x,y;
	while(scanf("%d",&m),m != 0) {
		for(int i = 0; i < N; i ++) {
			C[i] = Map[i] = -1;
			visit[i] = 0;
			mat[i].clear();
			vv[i].clear();
			v[i].clear();
		}
		int tm = m;
		memset(ind,0,sizeof(ind));
		n = 0;
		for(int i = 1; i <= m; i ++) {
			//x = i,y = i + 1;
			scanf("%d%d",&x,&y);
			x --,y --;
			if(x == y) continue;
			mat[x].push_back(y);
			mat[y].push_back(x);
			n = max(n,x);
			n = max(n,y);
		}
		++ n;
		printf("Case %d: ",++ cas);
		if(n == 1) {
			printf("1 1\n");
			continue;
		}
		assert(n != 1);
		cc = 0;
		block(n,mat);
		int tmp = cc;
		for(int i = 0; i < n; i ++) 
			if(C[i] > 0 || C[i] == -1) {
				size[++ cc] = -1;
				Map[i] = cc;
			}
		for(int i = 1; i <= tmp; i ++) {
			for(int j = 0; j < vv[i].size(); j ++)
				if(C[vv[i][j]] > 0) {
					ind[Map[vv[i][j]]] ++;
					ind[i] ++;
				}
		}
		long long ans = 1,tot = 0;
		
		if(cc == 1) {
			ans = n;
			printf("%lld %lld\n",2LL,(long long)n * (n - 1) / 2);
			continue;
		}
		memset(size,0,sizeof(size));
		for(int i = 0; i < n; i ++)
			size[Map[i]] ++;
		for(int i = 1; i <= cc; i ++)
			if(ind[i] == 1) tot ++,ans *= size[i];
		printf("%lld %lld\n",tot,ans);
	}
	return 0;
}
