#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
struct tree
{
    int lt,rt,mx;
}a[N * 4];

int c[N];
void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    if(lt == rt) {
        a[step].mx = c[lt];
        return;
    }
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
    a[step].mx = min(a[2 * step].mx,a[2 * step + 1].mx);
}

int query(int lt,int rt,int step)
{
    if(a[step].lt == lt && a[step].rt == rt) {
        return a[step].mx;
    }
    if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
    else return min(query(lt,a[2 * step].rt,2 * step),query(a[2 * step + 1].lt,rt,2 * step + 1));
}

int pre[N],nxt[N];
int stack[N];
int ans[N];

int main()
{
    int n;
    while(scanf("%d",&n) != EOF) {
        for(int i = 1; i <= n; i ++)
            scanf("%d",&c[i]);
        init(1,n,1);
        memset(pre,-1,sizeof(pre));
        memset(nxt,-1,sizeof(nxt));
        int top = 0;
        for(int i = 1; i <= n; i ++) {
            while(top && c[stack[top]] < c[i]) {
                nxt[stack[top]] = i;
                top --;
            }
            stack[++ top] = i;
        }
        top = 0;
        for(int i = n; i >= 1; i --) {
            while(top && c[stack[top]] < c[i]) {
                pre[stack[top]] = i;
                top --;
            }
            stack[++ top] = i;
        }        
        int ct = 0;
        for(int i = 1; i <= n; i ++) {
            if(c[i] < 150000) continue;
            if(nxt[i] == -1 && pre[i] == -1) {
                ans[++ ct] = i;
            }
            else if(pre[i] == -1) {
                int x = query(i,nxt[i],1);
                if(c[i] - x >= 150000) ans[++ ct] = i;
            }
            else if(nxt[i] == -1) {
                int x = query(pre[i],i,1);
                if(c[i] - x >= 150000) ans[++ ct] = i;
            }
            else {
                int x = query(pre[i],i,1);
                int y = query(i,nxt[i],1);
                if(c[i] - x >= 150000 && c[i] - y >= 150000) ans[++ ct] = i;
            }
        }
        for(int i = 1; i <= ct; i ++) {
            printf("%d",ans[i]);
            if(i < ct) printf(" ");
            else cout << endl;
        }
    }
    return 0;
}
 
/*
7
0 100000 0 200000 180000 200000 0
*/
