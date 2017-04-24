#include <bits/stdc++.h>
using namespace std;

const int N = 110;
vector<int> v[N];
int visit[N][N];
int c[N];
int ind[N];
int n;

struct point
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
	friend bool operator < (const point &p,const point &q) {
		return p.y < q.y;
	}
}a[N];

int lowbit(int x)
{
	return x & (-x);
}

bool flag;
void dfs(int step,int state)
{
	if(flag) return;
	if(step == n + 1) {
		flag = true;
		for(int i = 1; i <= n; i ++) {
			printf("%d %d\n",i,c[i]);
		}
		return;
	}
	int mix = -0x7fffffff,id;
	for(int i = 1; i <= n; i ++) {
		if(ind[i] > mix && !c[i]) {
			mix = ind[i];
			id = i;
		}
	}
	int x = id;
	int cc = 0;
	for(int i = 1; i <= 4; i ++) {
		if(!(state & (1 << (i - 1))) && cc) continue;
		if(!(state & (1 << (i - 1)))) cc ++;
		bool f = true;
		for(int j = 0; j < v[x].size(); j ++) {
			if(c[v[x][j]] == i) {
				f = false;
				break;
			}
		}
		if(f) {
			c[x] = i;
			for(int j = 0; j < v[x].size(); j ++) {
				if(!c[v[x][j]]) ind[c[v[x][j]]] --;
			}
			dfs(step + 1,state | ((1 << (i - 1))));
			c[x] = 0;
			for(int j = 0; j < v[x].size(); j ++) {
				if(!c[v[x][j]]) ind[c[v[x][j]]] ++;
			}
		}
	}
}
int main()
{
	char str[] = "abc";
	bool line = true;
	char s[10];
	while(scanf("%d",&n) != EOF) {
		gets(s);
		for(int i = 0; i < N; i ++) v[i].clear();
		int x,y;
		if(!line) printf("\n");
		line = false;
		for(int i = 0; i <= n; i ++)
			for(int j = 0; j <= n; j ++)
				visit[i][j] = 0;
		memset(ind,0,sizeof(ind));
		char *sig;
		sig = str;
		while((sig = gets(s)) && strlen(s) > 0) {
			sscanf(s,"%d-%d",&x,&y);
			if(visit[x][y]) continue;
			v[x].push_back(y);
			v[y].push_back(x);
			visit[x][y] = visit[y][x] = 1;
			ind[x] ++,ind[y] ++;
		}
		for(int i = 1; i <= n; i ++) {
			a[i] = point(i,ind[i]);
		}
		sort(a + 1,a + n + 1);
		flag = false;
		memset(c,0,sizeof(c));
//		cout << "enter" << endl;
		dfs(1,0);
//		cout << "out" << endl;
		if(sig == 0) return 0;
	}
	return 0;
}
