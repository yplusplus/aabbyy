#include<stdio.h>
#include<string.h>
#include<algorithm>
#include <iostream>
using namespace std;
#define MAXD 100010
typedef long long LL;
int N, M, node, T[MAXD], np[MAXD];
struct SegTree
{
    int ls, rs;
    int d, nd;
}st[3900000];
namespace ST
{
    int build(int x = 1, int y = N)
    {
        int cur = ++ node, mid = x + y >> 1;
        st[cur].d = st[cur].nd = 0;
        if(x < y) st[cur].ls = build(x, mid), st[cur].rs = build(mid + 1, y);
        return cur;
    }
    int insert(int pre, int k, int d)
    {
        int t = ++ node, cur = t, x = 1, y = N;
        for(;;)
        {
            st[cur].d = st[pre].d + d, st[cur].nd = st[pre].nd + (LL)k * d;
            if(x == y) break;
            int mid = x + y >> 1;
            if(k <= mid)
            {
                st[cur].ls = ++ node, st[cur].rs = st[pre].rs;
                cur = node, pre = st[pre].ls, y = mid;
            }
            else
            {
                st[cur].rs = ++ node, st[cur].ls = st[pre].ls;
                cur = node, pre = st[pre].rs, x = mid + 1;
            }
        }
        return t;
    }
}

LL query(int k, int t)
{
    int cur = T[t], x = 1, y = N;
    LL d = 0, nd = 0;
    if(k == 0) return 0;
    for(;;)
    {
        if(x == y)
        {
            d += st[cur].d, nd += st[cur].nd;
            break;
        }
        int mid = x + y >> 1;
        if(k <= mid) cur = st[cur].ls, y = mid;
        else
        {
            d += st[st[cur].ls].d, nd += st[st[cur].ls].nd;
            cur = st[cur].rs, x = mid + 1;
        }
    }
    return 1LL * k * d - nd + d;
}


int pos[MAXD],ss[MAXD],ee[MAXD];
LL sum[MAXD];
int c[MAXD];
long long b[MAXD],a[MAXD];
char s[25];

void myread(long long &x)
{
	int ct = 0;
	while(1) {
		s[ct] = getchar();
		if(isdigit(s[ct])) break;
	}
	ct ++;
	while(1) {
		s[ct] = getchar();
		if(isdigit(s[ct])) ct ++;
		else break;
	}
	x = 0;
	sort(s,s + ct);
	for(int i = ct - 1; i >= 0; i --)
		x = 10LL * x + (s[i] - '0');
}

void init()
{
    for(int i = 1; i <= N; i ++) {
        myread(a[i]);
        b[i] = a[i];
    }
    sort(b + 1,b + N + 1);
    int cnt = 1;
    for(int i = 2; i <= N; i ++)
        if(b[i] != b[cnt]) b[++ cnt] = b[i];
    for(int i = 1; i <= N; i ++) {
        int lt = 1,rt = cnt,mid;
        while(lt <= rt) {
            mid = (lt + rt) / 2;
            if(b[mid] == a[i]) {
                a[i] = mid;
                break;
            }
            if(b[mid] > a[i]) rt = mid - 1;
            else lt = mid + 1;
        }
    }
    N += 2;
    node = 0, T[0] = ST::build(), np[0] = node;
}

int lowbit(int x)
{
    return x & (-x);
}

int query(int n)
{
    int ans = 0;
    for(int i = n; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

void insert(int n)
{
    for(int i = n; i < MAXD; i += lowbit(i))
        c[i] ++;
}

void cal_interval(int n)
{
    memset(sum,0,sizeof(sum));
    memset(c,0,sizeof(c));
    ss[n + 1] = ee[n + 1] = n + 1;
    for(int i = 1; i <= n + 1; i ++) pos[i] = n + 1;
    int tot = 0;
    for(int i = n; i >= 1; i --) {
        int lt = i + 1,rt = ss[i + 1],x = n + 1,y = n,mid;
        if(pos[a[i]] <= n) insert(pos[a[i]]),tot ++;
        x = min(rt,pos[a[i]]);
        lt = x,rt = ee[i + 1];
        while(lt <= rt && tot) {
            mid = (lt + rt) / 2;
            int tmp = query(mid);
            if(tmp == 0) lt = mid + 1;
            else if(tmp >= 2) rt = mid - 1;
            else y = mid,lt = mid + 1;
        }
        ee[i] = y;
        ss[i] = x;
        pos[a[i]] = i;
        sum[i] = ee[i] - ss[i] + 1;
    }
    for(int i = 1; i <= n; i ++) {
        sum[i] += sum[i - 1];
        T[i] = ST::insert(T[i - 1],ss[i],1);
        if(ee[i] + 1 <= n) T[i] = ST::insert(T[i],ee[i] + 1,-1);
        np[i] = node;
    }
}

void read(long long &x)
{
    char cc;
    int flag = 1;
    while(1) {
        cc = getchar();
        if(isdigit(cc) || cc == '-') break;
    }
    if(cc == '-') flag = -1,x = 0;
    else x = cc -'0';
    while(1) {
        cc = getchar();
        if(isdigit(cc)) x = 10 * x + (cc - '0');
        else break;
    }
    x *= flag;
}

void solve()
{
    cal_interval(N - 2);
    int i, t, d, cur = 0;
    int n = N - 2;
    long long pre = 0,xx,yy;
    int x,y;
    for(i = 0; i < M; i ++)
    {
        read(xx);
        read(yy);
        //	x = xx,y = yy;
        x = xx + pre,y = yy - pre;
        if(sum[y] - sum[x - 1] == 0) {
            puts("0");
            pre = 0;
            continue;
        }
        long long tmp = query(n,y) - query(y,y) - (query(n,x - 1) - query(y,x - 1));
        tmp = sum[y] - sum[x - 1] - tmp;
        printf("%lld\n",tmp);
        pre = tmp;
    }
    //   cout << node << endl;
}

int main()
{
    //	freopen("1.in","r",stdin);
    while(scanf("%d%d", &N, &M) == 2)
    {
        init();
        solve();   
    }
    return 0;    
}
