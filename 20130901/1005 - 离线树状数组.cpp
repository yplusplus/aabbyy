#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
int a[20][N],b[20][N];
int c[N];

void build(int left,int right,int step)
{
    if(left == right) return;
    int mid = (left + right) / 2,i,lt = mid - left + 1;
    for(i = left; i <= right; i ++) {
        if(a[step][i] < c[mid]) lt --;
    }
    int lc = left,rc = mid + 1;
    for(i = left; i <= right; i ++) {
        if(a[step][i] < c[mid]) {
            a[step + 1][lc ++] = a[step][i];
            b[step][i] = b[step][i - 1] + 1;
        }
        else if(a[step][i] == c[mid] && lt) {
            lt --;
            a[step + 1][lc ++] = a[step][i];
            b[step][i] = b[step][i - 1] + 1;
        }
        else {
            a[step + 1][rc ++] = a[step][i];
            b[step][i] = b[step][i - 1];
        }
    }
    build(left,mid,step + 1);
    build(mid + 1,right,step + 1);
}

int query(int left,int right,int k,int lt,int rt,int step)
{
    if(left == right) return a[step][left];
    int mid = (lt + rt) / 2;
    int x = b[step][left - 1] - b[step][lt - 1];
    int y = b[step][right] - b[step][lt - 1];
    if(y - x >= k) return query(lt + x,lt + y - 1,k,lt,mid,step + 1);
    else return query(mid + left - lt - x + 1,mid + right - lt - y + 1,k - y + x,mid + 1,rt,step + 1);
}

struct point
{
    int x,y,val,id;
    friend bool operator < (const point &p,const point &q) {
        return p.val < q.val;
    }
    void read() {
        scanf("%d%d",&x,&y);
        x ++,y ++;
    }
}pt[N];

struct node
{
    int x,val;
    friend bool operator < (const node &p,const node &q) {
        return p.val < q.val;
    }
}f[N];

int lowbit(int x)
{
    return x & (-x);
}

void insert(int x,int y,long long a[])
{
    for(int i = x; i < N; i += lowbit(i))
        a[i] += y;
}

long long query(int x,long long a[])
{
    long long ans = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        ans += a[i];
    return ans;
}

long long ans[N],num[N],sum[N];
int main()
{
    int n,m,t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++) {
            scanf("%d",&c[i]);
            a[0][i] = c[i];
            f[i].x = i;
            f[i].val = c[i];
        }
        sort(c + 1,c + n + 1);
        build(1,n,0);
        scanf("%d",&m);
        for(int i = 1; i <= m; i ++) {
            pt[i].read();
            pt[i].id = i;
            int mid = (pt[i].y - pt[i].x + 2) / 2;
            pt[i].val = query(pt[i].x,pt[i].y,mid,1,n,0);
        }
        sort(f + 1,f + n + 1);
        sort(pt + 1,pt + m + 1);
        memset(num,0,sizeof(num));
        memset(sum,0,sizeof(sum));
        for(int i = 1,j = 1; i <= m; i ++) {
            while(j <= n && f[j].val < pt[i].val) {
               insert(f[j].x,1,num);
               insert(f[j].x,f[j].val,sum);
               j ++;
            }
            ans[pt[i].id] = (query(pt[i].y,num) - query(pt[i].x - 1,num)) * pt[i].val - (query(pt[i].y,sum) - query(pt[i].x - 1,sum));
        } 
        memset(num,0,sizeof(num));
        memset(sum,0,sizeof(sum));
        for(int i = m, j = n; i >= 1; i --) {
            while(j >= 1 && f[j].val > pt[i].val) {
               insert(f[j].x,1,num);
               insert(f[j].x,f[j].val,sum);
               j --;
            }
            ans[pt[i].id] -= (query(pt[i].y,num) - query(pt[i].x - 1,num)) * pt[i].val - (query(pt[i].y,sum) - query(pt[i].x - 1,sum));
        } 
        printf("Case #%d:\n",cas);
        for(int i = 1; i <= m; i ++) 
            printf("%I64d\n",ans[i]);
        printf("\n");
    }
    return 0;
}
                
        
            

