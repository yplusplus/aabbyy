#pragma comment(linker, "/STACK:1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 100010;
const long long mod = 1000000007;
struct trie
{
	trie *next[26];
	int id;
}e[N];

struct edge
{
	int v,next;
	char c;
}ex[N * 2];

int head[N];
int cc,cnt,map[N],rak[N],st[N],ed[N],R,times,val[N],dep[N];

void init(int c)
{
	e[c].id = c;
	for(int i = 0; i < 26; i ++) e[c].next[i] = NULL;
}

void addedge(int u,int v,char c)
{
	ex[cnt].v = v;
	ex[cnt].c = c;
	ex[cnt].next = head[u];
	head[u] = cnt ++;
}

queue<int> q;
void build_trie()
{
	while(!q.empty()) q.pop();
	q.push(1);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i != -1; i = ex[i].next) {
			if(map[ex[i].v] != -1) continue;
			if(e[map[u]].next[ex[i].c - 'a']) {
				map[ex[i].v] = e[map[u]].next[ex[i].c - 'a']->id;
			}
			else {
				init(cc);
				e[map[u]].next[ex[i].c - 'a'] = &e[cc];
				map[ex[i].v] = cc ++;
			}
			q.push(ex[i].v);
		}
	}
}

void get_rank(int u)
{
	rak[u] = R ++;
	for(int i = 0; i < 26; i ++)
		if(e[u].next[i]) get_rank(e[u].next[i]->id);
}

void dfs(int u,int fa,int hashval,int dp)
{
	st[u] = ++ times;
	val[u] = hashval;
	dep[u] = dp;
	for(int i = head[u]; i != -1; i = ex[i].next) {
		if(ex[i].v == fa) continue;
		dfs(ex[i].v,u,(26LL * hashval + (ex[i].c - 'a')) % mod,dp + 1);
	}
	ed[u] = times;
}

struct point
{
	int dp,id,val,hashcode;
	point() {}
	point(int dp,int id,int val,int hashcode):dp(dp),id(id),val(val),hashcode(hashcode) {}
	friend bool operator < (const point &p,const point &q) {
		if(p.dp != q.dp) return p.dp < q.dp;
		return p.id < q.id;
	}
}pt[N];

struct tree
{
	int lt,rt,val,hashcode;
}a[N * 4];

void init(int lt,int rt,int step)
{
	a[step].lt = lt;
	a[step].rt = rt;
	if(lt == rt) {
		a[step].val = pt[lt].val;
		a[step].hashcode = pt[lt].hashcode;
		return;
	}
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
	if(a[2 * step].val >= a[2 * step + 1].val) {
		a[step].val = a[2 * step].val;
		a[step].hashcode = a[2 * step].hashcode;
	}
	else {
		a[step].val = a[2 * step + 1].val;
		a[step].hashcode = a[2 * step + 1].hashcode;
	}
}

int query(int lt,int rt,int step,int &hashcode)
{
	if(a[step].lt == lt && a[step].rt == rt) {
		hashcode = a[step].hashcode;
		return a[step].val;
	}
	if(rt <= a[2 * step].rt) query(lt,rt,2 * step,hashcode);
	else if(lt > a[2 * step].rt) query(lt,rt,2 * step + 1,hashcode);
	else {
		int hashcode1,hashcode2;
		int val1 = query(lt,a[2 * step].rt,2 * step,hashcode1);
		int val2 = query(a[2 * step + 1].lt,rt,2 * step + 1,hashcode2);
		if(val1 >= val2) hashcode = hashcode1;
		else hashcode = hashcode2;
		return max(val1,val2);
	}
}

void find(int st,int ed,int dp,int &x,int &y,int n)
{
	x = y = -1;
	int lt = 1,rt = n,mid;
	while(lt <= rt) {
		mid = (lt + rt) / 2;
		if(pt[mid].dp < dp) lt = mid + 1;
		else if(pt[mid].dp > dp) rt = mid - 1;
		else if(pt[mid].id >= st) {
			x = mid;
			rt = mid - 1;
		}
		else lt = mid + 1;
	}
	lt = 1,rt = n;
	while(lt <= rt) {
		mid = (lt + rt) / 2;
		if(pt[mid].dp < dp) lt = mid + 1;
		else if(pt[mid].dp > dp) rt = mid - 1;
		else if(pt[mid].id <= ed) {
			y = mid;
			lt = mid + 1;
		}
		else rt = mid - 1;
	}
	if(x == -1) return;
	if(x <= y && pt[x].id >= st && pt[x].id <= ed) return;
	x = y = -1;
}

long long pp[N];

int main()
{
	pp[0] = 1;
	for(int i = 1; i < N; i ++) {
		pp[i] = 26LL * pp[i - 1] % mod;
	}
	int t,n,m,x,y;
	char s[15];
	scanf("%d",&t);
	while(t --) {
		scanf("%d",&n);
		cnt = 0;
		memset(head,-1,sizeof(head));
		cc = 1;
		init(0);
		memset(map,-1,sizeof(map));
		map[1] = 0;
		for(int i = 1; i < n; i ++) {
			scanf("%d%d%s",&x,&y,s);
			addedge(x,y,s[0]);
			addedge(y,x,s[0]);
		}
		build_trie();
		R = 0;
		get_rank(0);
		times = 0;
		dfs(1,1,0,0);
		for(int i = 1; i <= n; i ++)
			pt[i] = point(dep[i],st[i],rak[map[i]],val[i]);
		sort(pt + 1,pt + n + 1);
		init(1,n,1);
		scanf("%d",&m);
		while(m --) {
			scanf("%d%d",&x,&y);
			int dp = dep[x] + y;
			int vv = pp[y] * val[x] % mod;
			find(st[x],ed[x],dp,x,y,n);
			if(x == -1) printf("IMPOSSIBLE\n");
			else {
				int hashcode;
				query(x,y,1,hashcode);
				int ans = (hashcode - vv) % mod;
				if(ans < 0) ans += mod;
				printf("%d\n",ans);
			}
		}
	}	
	return 0;
}


