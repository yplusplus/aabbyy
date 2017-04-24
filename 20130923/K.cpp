#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long N = 250010;
struct tree
{
    int lt,rt;
    long long flag;
    long long mx,mix;
}a[N * 4];

long long c[N];

void update(int step)
{
    a[step].mx = max(a[2 * step].mx,a[2 * step + 1].mx);
    a[step].mix = min(a[2 * step].mix,a[2 * step + 1].mix);
}

void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    if(lt == rt) {
        a[step].flag = a[step].mx = a[step].mix = c[lt];
        return;
    }
    a[step].flag = 0;
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
    update(step);
}

void add(int step,long long c)
{
    a[step].flag += c;
    a[step].mx += c;
    a[step].mix += c;
}

void down(int step)
{
    if(!a[step].flag) return;
    add(2 * step,a[step].flag);
    add(2 * step + 1,a[step].flag);
    a[step].flag = 0;
}

int query(int step,int lt,int rt)
{
    if(a[step].mx < lt) return 0;
    if(a[step].mix > rt) return 0;
    if(a[step].mix >= lt && a[step].mx <= rt) return a[step].rt - a[step].lt + 1;
    down(step);
    return query(2 * step,lt,rt) + query(2 * step + 1,lt,rt);
}
    
void insert(int step,int lt,int rt,int c)
{
    if(a[step].mx < lt) return;
    if(a[step].mix > rt) return;
    if(a[step].mix >= lt && a[step].mx <= rt) {
        add(step,c);
        return;
    }
    down(step);
    insert(2 * step,lt,rt,c);
    insert(2 * step + 1,lt,rt,c);
    update(step);
}

void reset(int step)
{
    if(a[step].lt == a[step].rt) {
        c[a[step].lt] = a[step].flag;
        return;
    }
    down(step);
    reset(2 * step);
    reset(2 * step + 1);
}

int main()
{
    int n,m;
    char cd[5];
    int x,y,z;
    while(scanf("%d%d",&n,&m) != EOF) {
        for(int i = 1; i <= n; i ++) scanf("%I64d",&c[i]);
        sort(c + 1,c + n + 1); 
        init(1,n,1);
        while(m --) {
            scanf("%s",cd);
            if(cd[0] == 'C') {
                scanf("%d%d%d",&x,&y,&z);
                insert(1,x,y,z);
            }
            else {
                scanf("%d%d",&x,&y);
                printf("%d\n",query(1,x,y));
            }
            if(m % 8000 == 0) {
                reset(1);
                sort(c + 1,c + n + 1);
                init(1,n,1);
            }
        }
    }
    return 0;
}
    

