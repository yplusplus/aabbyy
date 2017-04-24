#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
vector<int> v[N];
struct point
{
	int id;
	char s[555];
	friend  bool operator < (const point &p,const point &q) {
		return strcmp(p.s,q.s) < 0;
	}
}a[N];

bool visit[N],flag[N][N][2];
int state[N];
int n,tot,ans[N][N],pos[N],deg[N][2];

bool cmp(char *s,char *str,int m)
{
	for(int i = 0; i < m; i ++)
		if(s[i] != str[i]) return false;
	return true;
}

void dfs(int u,int fg)
{
	visit[u] = 1;
	for(int j = 0; j < v[u].size(); j ++)
		ans[tot][pos[tot] ++] = v[u][j];
	for(int i = 1; i <= n; i ++)
		if(flag[u][i][fg] && !visit[i]) dfs(i,fg);
}

int main()
{
	freopen("heavy.in","r",stdin);
	freopen("heavy.out","w",stdout);
	int m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i ++) {
		scanf("%s",a[i].s);
		a[i].id = i;
		v[i].push_back(i);
	}
	sort(a + 1,a + n + 1);
	int i = 1;
	while(i <= n) {
		int j = i;
		while(j <= n && cmp(a[i].s,a[j].s,m)) j ++;
		for(int k = i; k < j; k ++)
			for(int r = k + 1; r < j; r ++)
				flag[a[k].id][a[r].id][0] = flag[a[r].id][a[k].id][0] = true;
		i = j;
	}
	for(int j = 1; j <= n; j ++) {
		int len = strlen(a[j].s);
		reverse(a[j].s,a[j].s + len);
	}
	sort(a + 1,a + n + 1);
	i = 1;
	while(i <= n) {
		int j = i;
		while(j <= n && cmp(a[i].s,a[j].s,m)) j ++;
		for(int k = i; k < j; k ++)
			for(int r = k + 1; r < j; r ++)
				flag[a[k].id][a[r].id][1] = flag[a[r].id][a[k].id][1] = true;
		i = j;
	}
	memset(visit,false,sizeof(visit));
	for(i = 1; i <= n; i ++) {
		if(visit[i]) continue;
		for(int j = i + 1; j <= n; j ++)
			if(flag[i][j][0] && flag[i][j][1]) {
				visit[j] = 1;
				v[i].push_back(j);
			}
	}
	for(i = 1; i <= n; i ++) {
		if(visit[i]) continue;
		for(int j = 1; j <= n; j ++) {
			if(visit[j] || i == j) continue;
			if(flag[i][j][0]) state[i] |= 1,deg[i][0] ++;
			else if(flag[i][j][1]) state[i] |= 2,deg[i][1] ++;
		}
		if(deg[i][0] == 0 && deg[i][1] == 0) {
			visit[i] = true;
			++ tot;
			for(int j = 0; j < v[i].size(); j ++) {
				ans[tot][pos[tot] ++] = v[i][j];
			}
		}
	}
	while(1) {
		int idx1 = -1,idx2 = -1;
		for(i = 1; i <= n; i ++) {
			if(visit[i]) continue;
			if(deg[i][0] == 0 && deg[i][1] == 0) {
				tot ++;
				for(int j = 0; j < v[i].size(); j ++) {
					ans[tot][pos[tot] ++] = v[i][j];
				}
				visit[i] = true;
			}
			else if(deg[i][0] && deg[i][1]) {
				idx2 = i;
			}
			else if(deg[i][0] == 0 || deg[i][1] == 0) {
				idx1 = i;
			}
		}
		if(idx1 == -1 && idx2 == -1) break;
		++ tot;
		//cout << idx1 << " " << idx2 << " " << endl;
		//if(idx1 != -1) cout << "Fuck " << deg[idx1][0] << " " << deg[idx1][1] << " " << flag[idx1][1][0] << endl;
		if(idx1 != -1 && deg[idx1][0]) dfs(idx1,0);
		else if(idx1 != -1) dfs(idx1,1);
		else dfs(idx2,0);
		for(i = 0; i < pos[tot]; i ++) {
			for(int j = 1; j <= n; j ++) {
				if(visit[j]) continue;
				if(flag[ans[tot][i]][j][0]) deg[j][0] --;
				else if(flag[ans[tot][i]][j][1]) deg[j][1] --;
			}
		}
	}
	printf("%d\n",tot);
	for(i = 1; i <= tot; i ++) {
		printf("%d",pos[i]);
		sort(ans[i],ans[i] + pos[i]);
		for(int j = 0; j < pos[i]; j ++) {
			printf(" %d",ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
