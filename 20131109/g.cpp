#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

const int N = 100010;
struct trie
{
	trie *next[2],*pre;
	int digit,times;
}e[6000010],*root;

int cnt = 0;
set<trie*> st[N];
void init(int cnt)
{
	e[cnt].next[0] = e[cnt].next[1] = e[cnt].pre = NULL;
	e[cnt].times = 0;
}

void insert(long long x)
{
	trie *p = root;
	for(int i = 59; i >= 0; i --) {
		int id = ((x & (1LL << i)) != 0);
		if(!p->next[id]) {
			init(cnt);
			p->next[id] = &e[cnt ++];
			p->next[id]->pre = p;
			p->next[id]->digit = id;
		}
		p = p->next[id];
	}
	p->times ++;
}

void init()
{
	init(0);
	cnt = 0;
	root = &e[cnt ++];
}

struct edge
{
	int v,next;
	long long dis;
}et[N * 2];

int head[N],ct;

void addedge(int u,int v,long long dis)
{
//	cout << u << " " << v << endl;
	et[ct].v = v;
	et[ct].dis = dis;
	et[ct].next = head[u];
	head[u] = ct ++;
}

void read(long long &x)
{
	int c;
	while(1) {
		c = getchar();
		if(isdigit(c)) break;
	}
	x = c - '0';
	while(1) {
		c = getchar();
		if(isdigit(c)) x = 10LL * x + (c - '0');
		else break;
	}
}

long long xr[N];
void dfs(int u,int pre,long long val)
{
	xr[u] = val;
	for(int i = head[u]; i != -1; i = et[i].next)
		if(et[i].v != pre) dfs(et[i].v,u,val ^ et[i].dis);
}

struct point
{
	int id;
	long long val,times;
	trie *p;
	friend bool operator < (const point &p,const point &q) {
		return p.val < q.val;
	}
	point() {}
	point(int id,long long val,long long times,trie *p):id(id),val(val),times(times),p(p) {}
};

priority_queue<point> pq;

point get_next(point now)
{
	trie *p = now.p;
	long long val = now.val;
	int dep = 0;
	int id = now.id;
	while(1) {
		int flag = 0;
		int dt = ((1LL << dep) & xr[id]) != 0;
		if(dt == p->digit) flag = 0;
		else flag = 1;
		val -= ((1LL << dep) * flag);
		if(p == root) {
			return point(-1,-1,-1,p);
		}
		int digit = p->digit;
		p = p->pre;
		if(p->next[digit ^ 1] && now.val > val + (flag ^ 1) * (1LL << dep)) {
			p = p->next[digit ^ 1];
			val += (flag ^ 1) * (1LL << dep);
			dep --;
//			st[id].insert(p);
			while(dep >= 0) {
				dt = ((1LL << dep) & xr[id]) != 0;
				if(p->next[dt ^ 1]) {
					val += 1LL << dep;
					p = p->next[dt ^ 1];
				}
				else {
					p = p->next[dt];
				}
//				st[id].insert(p);
				dep --;
			}
			return point(id,val,p->times,p);
		}
		dep ++;
	}
}

long long ans[N * 2];
int ask[N * 2];
int main()
{	
	int n;
	long long x,y,z;
	while(scanf("%d",&n), n != 0) {
		for(int i = 0; i <= n; i ++)
			head[i] = -1;
		ct = 0;
		init();
		for(int i = 1; i <= n; i ++) st[i].clear();
		for(int i = 1; i < n; i ++) {
			read(x);
			read(y);
			read(z);
			addedge(x,y,z);
			addedge(y,x,z);
		}
		int r;
		scanf("%d",&r);
		int maxn = 0;
		for(int i = 1; i <= r; i ++) {
			scanf("%d",&ask[i]);
			maxn = max(maxn,ask[i]);
		}
		dfs(1,0,0);
		for(int i = 1; i <= n; i ++)
			insert(xr[i]);
		while(!pq.empty()) pq.pop();
		//for(int i = 1; i <= n; i ++)
			//cout << xr[i] << " ";
		//cout << endl;
		for(int i = 1; i <= n; i ++) {
			trie *p = root;
			long long val = 0;
			for(int j = 59; j >= 0; j --) {
				int dt = ((1LL << j) & xr[i]) != 0;
				if(p->next[dt ^ 1]) {
					p = p->next[dt ^ 1];
					val += (1LL << j);
				}
				else p = p->next[dt];
//				st[i].insert(p);
			}
			pq.push(point(i,val,p->times,p));
			/*
			if(p->times > 1) {
				pq.push(point(i,val,p->times - 1,p));
			}
			else {
				point tmp = get_next(point(i,val,0,p));
				if(tmp.val >= 0) pq.push(tmp);
			}
			*/
		}
		//cout << "omg" << endl;
		for(int i = 1; i <= maxn; i ++) {
			if(pq.empty() || i > 1LL * n * (n - 1)) {
				ans[i] = -1;
				continue;
			}
			point tmp = pq.top();
			pq.pop();
			ans[i] = tmp.val;
			tmp.times --;
			if(tmp.times > 0) {
				pq.push(tmp);
			}
			else {
				tmp = get_next(tmp);
				if(tmp.val >= 0) pq.push(tmp);
			}
		}
		for(int i = 1; i <= r; i ++)
			printf("%I64d\n",ans[ask[i]]);
	}
	return 0;
}
