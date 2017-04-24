#include <bits/stdc++.h>
using namespace std;

const int M = 100010;
const int N = 800010;
struct tree
{
	int cover,num;
}a[N * 4];

struct point
{
	int x,y,height,id;
	void read() {
		scanf("%d%d%d",&x,&y,&height);
		x ++;
	}
	friend bool operator < (const point &p,const point &q) {
		return p.height < q.height;
	}
}b[M];

void init(int lt,int rt,int step)
{
	a[step].cover = 0;
	a[step].num = 0;
	if(lt == rt) return;
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid + 1,rt,2 * step + 1);
}

void insert(int lt,int rt,int step,int id,int L,int R)
{
	if(L == lt && R == rt) {
		a[step].cover = id;
		return;
	}
	if(a[step].cover) {
		a[2 * step].cover = a[step].cover;
		a[2 * step + 1].cover = a[step].cover;
		a[step].cover = 0;
	}
	int mid = (L + R) >> 1;
	if(rt <= mid) insert(lt,rt,2 * step,id,L,mid);
	else if(lt > mid) insert(lt,rt,2 * step + 1,id,mid + 1,R);
	else {
		insert(lt,mid,2 * step,id,L,mid);
		insert(mid + 1,rt,2 * step + 1,id,mid + 1,R);
	}
}

void add(int lt,int rt,int step,int L,int R)
{
	if(L == lt && rt == R) {
		a[step].num ++;
		return;
	}
	if(a[step].num) {
		 a[2 * step].num += a[step].num;
		 a[2 * step + 1].num += a[step].num;
		 a[step].num = 0;
	}
	int mid = (L + R) >> 1;
	if(rt <= mid) add(lt,rt,2 * step,L,mid);
	else if(lt > mid) add(lt,rt,2 * step + 1,mid + 1,R);
	else {
		add(lt,mid,2 * step,L,mid);
		add(mid + 1,rt,2 * step + 1,mid + 1,R);
	}
}

int c[N],lt[M],rt[M];
long long ans[M];
void down(int step,int L,int R)
{
	if(L == R) {
		if(!a[step].cover) return;
		int lenx = c[L - 1] + 1;
		int leny = c[L];
		ans[a[step].cover] += (long long)a[step].num * (leny - lenx + 1);
		return;
	}
	if(a[step].cover) {
		a[2 * step].cover = a[step].cover;
		a[2 * step + 1].cover = a[step].cover;
	}
	if(a[step].num) {
		a[2 * step].num += a[step].num;
		a[2 * step + 1].num += a[step].num;
	}
	int mid = (L + R) >> 1;
	down(2 * step,L,mid);
	down(2 * step + 1,mid + 1,R);
}

int cnt;

int find(int x)
{
	int lt = 1,rt = cnt,mid;
	while(lt <= rt) {
		mid = (lt + rt) / 2;
		if(c[mid] == x) return mid;
		if(c[mid] > x) rt = mid - 1;
		else lt = mid + 1;
	}
}
int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 1; i <= n; i ++) {
			scanf("%d%d",&lt[i],&rt[i]);
			lt[i] ++;
		}
		int tot = 0;
		for(int i = 1; i <= m; i ++) {
			b[i].read();
			b[i].id = i;
			c[++ tot] = b[i].x;
			c[++ tot] = b[i].y;
			c[++ tot] = b[i].x - 1;
			if(b[i].x != b[i].y) c[++ tot] = b[i].y - 1;
		}
		sort(b + 1,b + m + 1);
		for(int i = 1; i <= n; i ++) {
			c[++ tot] = lt[i];
			c[++ tot] = rt[i];
			if(lt[i] != rt[i]) c[++ tot] = rt[i] + 1;
			c[++ tot] = lt[i] - 1;
		}
		sort(c + 1,c + tot + 1);
		cnt = 0;
		for(int i = 1; i <= tot; i ++)
			if(i == 1 || c[i] != c[cnt]) c[++ cnt] = c[i];
		init(1,cnt,1);
		for(int i = 1; i <= m; i ++) {
			int x = find(b[i].x);
			int y = find(b[i].y);
			insert(x,y,1,b[i].id,1,cnt);
		}
		for(int i = 1; i <= n; i ++) {
			int x = find(lt[i]);
			int y = find(rt[i]);
			add(x,y,1,1,cnt);
		}
		memset(ans,0,sizeof(ans));
		down(1,1,cnt);
		for(int i = 1; i <= m; i ++) printf("%lld\n",ans[i]);
		cout << endl;
	}
	return 0;
}
