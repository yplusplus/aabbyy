#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
const long long oo = 1LL << 60;
struct tree
{
    int lt,rt;
    long long lx,rx,mx,lid,rid,lpos,rpos,sum,flag;
}a[N * 4];

void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    a[step].lx = a[step].rx = a[step].mx = -oo;
    a[step].lid = a[step].lpos = lt;
    a[step].rid = a[step].rpos = rt;
    a[step].sum = a[step].flag = 0;
    if(lt == rt) return;
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
}

void update(int step)
{
    if(a[2 * step].mx > a[2 * step + 1].mx) {
        a[step].mx = a[2 * step].mx;
        a[step].lid = a[2 * step].lid;
        a[step].rid = a[2 * step].rid;
    }
    else {
        a[step].mx = a[2 * step + 1].mx;
        a[step].lid = a[2 * step + 1].lid;
        a[step].rid = a[2 * step + 1].rid;
    }
    
    if(a[2 * step].rx + a[2 * step + 1].lx > a[step].mx) {
        a[step].mx = a[2 * step].rx + a[2 * step + 1].lx;
        a[step].lid = a[2 * step].rpos;
        a[step].rid = a[2 * step + 1].lpos;
    }
    
    if(a[2 * step].lx > a[2 * step].sum + a[2 * step + 1].lx) {
        a[step].lx = a[2 * step].lx;
        a[step].lpos = a[2 * step].lpos;
    }
    else {
        a[step].lx = a[2 * step].sum + a[2 * step + 1].lx;
        a[step].lpos = a[2 * step + 1].lpos;
    }
    
    if(a[2 * step + 1].rx > a[2 * step + 1].sum + a[2 * step].rx) {
        a[step].rx = a[2 * step + 1].rx;
        a[step].rpos = a[2 * step + 1].rpos;
    }
    else {
        a[step].rx = a[2 * step + 1].sum + a[2 * step].rx;
        a[step].rpos = a[2 * step].rpos;
    }
    a[step].sum = a[2 * step].sum + a[2 * step + 1].sum;
}
  
void insert(int pos,int v,int step)
{
    if(a[step].lt == a[step].rt) {
        a[step].sum += v;
        a[step].flag ++;
        a[step].lx = a[step].rx = a[step].sum;
        if(a[step].flag > 1) {
            a[step].mx = a[step].sum;
        }
        return;
    }
    if(pos <= a[2 * step].rt) insert(pos,v,2 * step);
    else insert(pos,v,2 * step + 1);
    update(step);
}
       
struct point
{
    int x,y,z;
    point() {}
    point(int x,int y,int z):x(x),y(y),z(z) {}
    void read() {
        scanf("%d%d%d",&x,&y,&z);
    }
    friend bool operator < (const point &p,const point &q) {
        return p.x < q.x;
    }
}c[N];

int solve(int a[],int n)
{
    sort(a + 1,a + n + 1);
    int tmp = 1;
    for(int i = 2; i <= n; i ++)
       if(a[i] != a[tmp]) a[++ tmp] = a[i];
    return tmp;
}

int find(int X[],int len,int x)
{
    int lt = 1,rt = len,mid;
    while(lt <= rt) {
        mid = (lt + rt) / 2;
        if(X[mid] == x) return mid;
        if(X[mid] > x) rt = mid - 1;
        else lt = mid + 1;
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int X[N],Y[N];
    int c1 = 0,c2 = 0;
    for(int i = 1; i <= n; i ++) {
        c[i].read();
        X[i] = c[i].x;
        Y[i] = c[i].y;
    }
    c1 = solve(X,n);
    c2 = solve(Y,n);
    for(int i = 1; i <= n; i ++) {
        c[i].x = find(X,c1,c[i].x);
        c[i].y = find(Y,c2,c[i].y);
    }
    long long ans = -oo;
    int x1 = -1,x2 = -1,y1 = -1,y2 = -1;
    sort(c + 1,c + n + 1);
    for(int i = 1; i <= c1; i ++) {
        init(1,c2,1);
        int pos = 1;
        for(int j = i; j <= c1; j ++) {
            while(pos <= n && c[pos].x < j) pos ++;
            while(pos <= n && c[pos].x == j) {
                insert(c[pos].y,c[pos].z,1);
                pos ++;
            }
            if(a[1].mx > ans) {
                ans = a[1].mx;
                x1 = i,x2 = j;
                y1 = a[1].lid;
                y2 = a[1].rid;
            }
        }
    }
    //cout << ans << endl;
    cout << X[x1] << " " << X[x2] << endl;
    cout << Y[y1] << " " << Y[y2] << endl;
    return 0;
}

