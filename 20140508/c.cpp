#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
bool dp[N][N];
int prex[N][N],prey[N][N];
struct edge
{
	int v,next;
}e[N * 100];

int head[N],cnt;

void addedge(int u,int v)
{
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

int ansx[N],ansy[N];
int c1,c2;
int x1,x2;
short int res2[N][N],res1[N][N];

void output(int st,int ed)
{
	if(st == x1 && ed == x2) return;
	if(prex[st][ed] == st) {
		output(st,prey[st][ed]);
		ansy[++ c2] = prey[st][ed];
	}
	else {
		output(prex[st][ed],ed);
		ansx[++ c1] = prex[st][ed];
	}
}

int pos1[N],pos2[N];

int main()
{
	freopen("express.in","r",stdin);
	freopen("express.out","w",stdout);
	int y1,y2;
	int n,m;
	scanf("%d%d",&n,&m);
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	memset(head,-1,sizeof(head));
	int x,y;
	while(m --) {
		scanf("%d%d",&x,&y);
		addedge(y,x);
	}
	if(x1 > y1) swap(x1,y1);
	if(x2 > y2) swap(x2,y2);
	//puts("over");
	dp[x1][x2] = true;
    res1[x1][++ pos1[x1]] = x2;
	res2[x2][++ pos2[x2]] = x1;
	memset(prex,-1,sizeof(prex));
	memset(prey,-1,sizeof(prey));
	for(int k = min(x1,x2); k <= max(y1,y2); k ++) {
	  if(k != x2 && k != y2 && k <= y1 && k >= x1) {
		for(int ii = head[k],i; ii != -1; ii = e[ii].next) {
			i = e[ii].v;
			for(int jj = 1,j; jj <= pos1[i]; jj ++) {
				j = res1[i][jj];
				if(k == j || dp[k][j]) continue;
				dp[k][j] = true;
				prex[k][j] = i;
				prey[k][j] = j;
				res1[k][++ pos1[k]] = j;
				res2[j][++ pos2[j]] = k;
			}
		}
	  }
	  if(k != x1 && k != y1 && k <= y2 && k >= x2) {
		for(int jj = head[k],j; jj != -1; jj = e[jj].next) {
			j = e[jj].v;
			for(int ii = 1,i; ii <= pos2[j]; ii ++) {
				i = res2[j][ii];
				if(k == i || dp[i][k]) continue;
				dp[i][k] = true;
				prex[i][k] = i;
				prey[i][k] = j;
				res1[i][++ pos1[i]] = k;
				res2[k][++ pos2[k]] = i;
			}
		}
	  }
	}
	if(!dp[y1][y2]) {
		puts("NO");
		return 0;
	}
	output(y1,y2);
	ansx[c1 + 1] = y1,ansy[c2 + 1] = y2;
	printf("YES\n");
	for(int i = 1; i <= c1 + 1; i ++) {
		printf("%d",ansx[i]);
		if(i == c1 + 1) printf("\n");
		else printf(" ");
	}
	for(int i = 1; i <= c2 + 1; i ++) {
		printf("%d",ansy[i]);
		if(i == c2 + 1) printf("\n");
		else printf(" ");
	}
	return 0;
}
