#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int wa[N],wb[N],wv[N],wss[N];

int cmp(int *r,int a,int b,int len)
{
    return r[a] == r[b] && r[a + len] == r[b + len];
}

void da(int *r,int *sa,int n,int m)
{

    int i,j,p,*x = wa,*y = wb,*t;
    for(i = 0; i < m; i ++) wss[i] = 0;
    for(i = 0; i < n; i ++) wss[x[i] = r[i]] ++;
    for(i = 1; i < m; i ++) wss[i] += wss[i - 1];
    for(i = n -  1; i >= 0; i --) sa[-- wss[x[i]]] = i;
    for(j = p = 1; p < n; j *= 2,m = p) {
        for(p = 0, i = n - j; i < n; i ++) y[p ++] = i;
        for(i = 0; i < n; i ++) if(sa[i] >= j) y[p ++] = sa[i] - j;
        for(i = 0; i < n; i ++) wv[i] = x[y[i]];
        for(i = 0; i < m; i ++) wss[i] = 0;
        for(i = 0; i < n; i ++) wss[wv[i]] ++;
        for(i = 1; i < m; i ++) wss[i] += wss[i - 1];
        for(i = n - 1; i >= 0; i --) sa[-- wss[wv[i]]] = y[i];
        for(t = x,x = y,y = t,p = 1,x[sa[0]] = 0, i = 1; i < n; i ++)
            x[sa[i]] = cmp(y,sa[i - 1],sa[i],j) ? p - 1 : p ++;
    }
}

int rak[N],height[N];
void calheight(int *r,int *sa,int n)
{
    int i,j,k = 0;
    for(i = 1; i < n; i ++) rak[sa[i]] = i;
    for(i = 0; i < n - 1; height[rak[i ++]] = k)
        for(k ? k -- : 0,j = sa[rak[i] - 1]; r[i + k] == r[j + k]; k ++);
}

int f[20][N],bit[N];
int sa[N],r[N],n;

void rmq_init(int n)
{
    for(int i = 0; i <= n; i ++) f[0][i] = height[i];
    for(int j = 1; (1 << j) <= n; j ++) {
        for(int i = 1; i <= n; i ++) {
            if(i + (1 << (j - 1)) <= n) f[j][i] = min(f[j - 1][i],f[j - 1][i + (1 << (j - 1))]);
            else f[j][i] = f[j - 1][i];
        }
    }
    bit[0] = bit[1] = 0;
    for(int i = 1; (1 << i) < N; i ++)
        for(int j = (1 << i); j < (1 << (i + 1)) && j < N; j ++)
            bit[j] = i;
}

int rmq_query(int lt,int rt)
{
    int len = bit[rt - lt + 1];
    return min(f[len][lt],f[len][rt - (1 << len) + 1]);
}

int query(int x,int y)
{
    if(x == y) return n - sa[x];
    return rmq_query(x + 1,y);
}

long long a[N],sum[N],dp[N];

void init()
{
	for(int i = n; i >= 1; i --) {
		if(height[i + 1] == 0) continue;
		else {
			int lt = i + 1,rt = n,mid,pos;
			while(lt <= rt) {
				mid = (lt + rt) / 2;
				if(mid == (i + 1)) {
					pos = mid;
					lt = mid + 1;
				}
				else if(query(i + 1,mid) >= height[i + 1]) {
					pos = mid;
					lt = mid + 1;
				}
				else rt = mid - 1;
			}
			dp[i] = 1LL * height[i + 1] * (pos - i) + dp[pos];
		}
	}
}

char s[N];
int main()
{
    scanf("%s",s);
    n = strlen(s);
    for(int i = 0; i < n; i ++) r[i] = s[i];
    da(r,sa,n + 1,256);
    calheight(r,sa,n + 1);
    rmq_init(n);
    for(int i = 1; i <= n; i ++) sum[i] = sum[i - 1] + (n - sa[i]);
    init();
    int q,x,y;
    scanf("%d",&q);
    while(q --) {
        scanf("%d%d",&x,&y);
        x --,y --;
        int pos = rak[x];
        int lt = 1,rt = pos - 1,mid,xx = pos,yy = pos;
        while(lt <= rt) {
            mid = (lt + rt) >> 1;
            if(query(mid,pos) >= y - x + 1) xx = mid,rt = mid - 1;
            else lt = mid + 1;
        }
        lt = pos,rt = n;
        while(lt <= rt) {
            mid = (lt + rt) >> 1;
            if(query(pos,mid) >= y - x + 1) yy = mid,lt = mid + 1;
            else rt = mid - 1;
        }
		int len = yy - xx + 1;
        long long ans = 1LL * (y - x) * len;
		ans += sum[xx - 1];
        ans += dp[yy];
		printf("%I64d\n",ans);
    }
    return 0;
}

