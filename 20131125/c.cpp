#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int oo = 1000000000;
const int N = 1000010;

struct tree
{
    int lt,rt,mix;
}a[N * 4];

int b[N],c[N],nxt[N],f[N];
void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    if(lt == rt) {
        a[step].mix = f[lt];
        return;
    } 
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
    a[step].mix = min(a[2 * step].mix,a[2 * step + 1].mix);
}
    
int query(int lt,int rt,int step)
{
    if(a[step].lt == lt && a[step].rt == rt) return a[step].mix;
    if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
    else return min(query(lt,a[2 * step].rt,2 * step),query(a[2 * step + 1].lt,rt,2 * step + 1));
}

void read(int &x)
{
    char c;
    while(1) {
        c = getchar();
        if(isdigit(c)) break;
    }
    x = c - '0';
    while(1) {
        c = getchar();
        if(isdigit(c)) x = 10 * x + (c - '0');
        else break;
    }
}

int find(int x,int n)
{
    int lt = 1,rt = n,mid;
    while(lt <= rt) {
        mid = (lt + rt) / 2;
        if(c[mid] == x) return mid;
        if(c[mid] > x) rt = mid - 1;
        else lt = mid + 1;
    }
}

int main()
{
    int n,m,x,y;
    while(scanf("%d%d",&n,&m) != EOF) {
        if(!n && !m) break;
        for(int i = 1; i <= n; i ++) {
            read(b[i]);
            c[i] = b[i];
        }
        sort(c + 1,c + n + 1);
        int cnt = 1;
        for(int i = 1; i <= n; i ++) if(c[i] != c[cnt]) c[++ cnt] = c[i];
        for(int i = 1; i <= n; i ++) b[i] = find(b[i],cnt);
        for(int i = 0; i <= cnt; i ++) nxt[i] = oo;
        for(int i = n; i >= 1; i --) {
            f[i] = nxt[b[i]];
            nxt[b[i]] = i;
        }
        init(1,n,1);
        while(m --) {
            read(x);
            read(y);
            int ans = query(x,y,1);
            if(ans > y) printf("OK\n");
            else printf("%d\n",c[b[ans]]);
        }    
        cout << endl;
    }  
    return 0;
}    


