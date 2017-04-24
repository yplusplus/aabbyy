#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 50010;
int nxt[N],map[1000010];

int lowbit(int x)
{
    return x & (-x);
}

long long a[N];

void insert(int x,int y)
{
    for(int i = x; i < N; i += lowbit(i)) a[i] += y;
}

long long query(int x)
{
    long long ans = 0;
    for(int i = x; i > 0; i -= lowbit(i)) ans += a[i];
    return ans;
}

struct point
{
    int x,y,id;
    friend bool operator < (const point &p,const point &q) {
        return p.x < q.x;
    }
}c[N * 4];

int b[N];
long long ans[N * 4];

int main()
{
    int t,n,m;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++) scanf("%d",&b[i]);
        memset(map,-1,sizeof(map));
        memset(a,0,sizeof(a));
        scanf("%d",&m);
        for(int i = 1; i <= m; i ++) {
            c[i].id = i;
            scanf("%d%d",&c[i].x,&c[i].y);
        }
        sort(c + 1,c + m + 1);
        //for(int i = 1; i <= m; i ++) cout << c[i].id << endl;
        for(int i = n; i >= 1; i --) {
            nxt[i] = map[b[i]];
            map[b[i]] = i;
        }
        //cout << nxt[3] << endl;
        for(int i = m,j = n; i >= 1; i --) {
            while(j && j >= c[i].x) {
                insert(j,b[j]);
                if(nxt[j] != -1) {
                    insert(nxt[j],-b[j]);
          //          cout << "fuck" << " " << i << endl;
                }
                j --;
            }
            ans[c[i].id] = query(c[i].y);
        }
        for(int i = 1; i <= m; i ++) printf("%I64d\n",ans[i]);
    }
    return 0;
}