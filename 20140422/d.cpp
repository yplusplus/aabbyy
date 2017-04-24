#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
struct point
{
	int x,y,z;
	void read() {
		scanf("%d%d%d",&x,&y,&z);
	}
}a[N];
struct node
{
	int id;
	long long d1,d2;
	node() {}
	node(long long d1,long long d2,int id = 0):d1(d1),d2(d2),id(id) {}
	friend bool operator < (const node &p,const node &q) {
		if(p.d1 != q.d1) return p.d1 < q.d1;
		return p.d2 < q.d2;
	}
}b[N],ask[N];

bool cmpx(const node &p,const node &q) 
{
	return p.d1 < q.d1;
}

bool cmpy(const node &p,const node &q)
{
	return p.d2 < q.d2;
}

int lowbit(int x)
{
	return x & (-x);
}

void insert(int x,int y,int a[])
{
	for(int i = x; i < N; i += lowbit(i)) a[i] += y;
}

int query(int x,int a[])
{
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		ans += a[i];
	return ans;
}

long long sqr(int x)
{
	return 1LL * x * x;
}

long long dist(point a,point b)
{
	return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}

long long c[N];
int num[N];
int find(long long x,int n)
{
	int lt = 1,rt = n,mid;
	while(lt <= rt) {
		mid = (lt + rt) >> 1;
		if(c[mid] == x) return mid;
		if(c[mid] > x) rt = mid - 1;
		else lt = mid + 1;
	}
}

int find2(long long x,int n)
{
	int ans = -1,lt = 1,rt = n,mid;
	while(lt <= rt) {
		mid = (lt + rt) >> 1;
		if(c[mid] <= x) {
			ans = mid;
			lt = mid + 1;
		}
		else rt = mid - 1;
	}
	return ans;
}

long long ans[N];
void solve(int n)
{
	for(int i = 1; i <= n; i ++) a[i].read();
	int tot = 0;
	for(int i = 3; i <= n; i ++) {
		b[++ tot] = node(dist(a[1],a[i]),dist(a[2],a[i]),i);
	}
	sort(b + 1,b + tot + 1);
	int cc = 0;
	for(int i = 1; i <= tot; i ++) c[i] = b[i].d2;
	sort(c + 1,c + tot + 1);
	for(int i = 1; i <= tot; i ++)
		if(i == 1 || c[i] != c[cc]) c[++ cc] = c[i];
	memset(num,0,sizeof(num));
	int m;
	scanf("%d",&m);
	for(int i = 1; i <= m; i ++) {
		scanf("%lld%lld",&ask[i].d1,&ask[i].d2);
		ask[i].id = i;
		ask[i].d1 *= ask[i].d1;
		ask[i].d2 *= ask[i].d2;
	}
	sort(ask + 1,ask + m + 1);
	memset(ans,0,sizeof(ans));
	for(int i = 1,j = 1; i <= m; i ++) {
		while(j <= tot && b[j].d1 <= ask[i].d1) {
			int pos = find(b[j].d2,tot);
			insert(pos,1,num);
			j ++;
		}
		int pos = find2(ask[i].d2,tot);
		if(pos != -1) ans[ask[i].id] = -query(pos,num);
	}
	sort(b + 1,b + tot + 1,cmpx);
	for(int i = 1; i <= m; i ++) {
		int lt = 1,rt = tot,mid,ccc = 0;
		while(lt <= rt) {
			mid = (lt + rt) >> 1;
			if(ask[i].d1 >= b[mid].d1) ccc = mid,lt = mid + 1;
			else rt = mid - 1;
		}
		ans[ask[i].id] += ccc;
	}
	sort(b + 1,b + tot + 1,cmpy);
	for(int i = 1; i <= m; i ++) {
		int lt = 1,rt = tot,mid,ccc = 0;
		while(lt <= rt) {
			mid = (lt + rt) >> 1;
			if(ask[i].d2 >= b[mid].d2) ccc = mid,lt = mid + 1;
			else rt = mid - 1;
		}
		ans[ask[i].id] += ccc;
	}
	for(int i = 1; i <= m; i ++)
		printf("%lld\n",ans[i]);
}

int main()
{
	int n;
	while(scanf("%d",&n) != EOF) solve(n);
	return 0;
}
