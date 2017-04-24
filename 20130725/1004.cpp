#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 100010;
struct tree
{
    int lt,rt;
    int flag,sum0,sum1,first;
    int dis() {
        return rt - lt + 1;
    }
}a[N * 4];

void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    a[step].flag = 0;
    a[step].sum1 = 0;
    a[step].sum0 = rt - lt + 1;
    a[step].first = lt;
    if(lt == rt) return;
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
}

void down(int step)
{
    a[2 * step].flag = a[step].flag;
    a[2 * step + 1].flag = a[step].flag;
    if(a[step].flag == 1) {
        a[2 * step].sum1 = a[2 * step].dis();
        a[2 * step].first = a[2 * step + 1].first = -1;
        a[2 * step].sum0 = 0;
        a[2 * step + 1].sum1 = a[2 * step + 1].dis();
        a[2 * step + 1].sum0 = 0;
    }
    else {
        a[2 * step].first = a[2 * step].lt;
        a[2 * step + 1].first = a[2 * step + 1].lt;
        a[2 * step].sum1 = a[2 * step + 1].sum1 = 0;
        a[2 * step].sum0 = a[2 * step].dis();
        a[2 * step + 1].sum0 = a[2 * step + 1].dis();
    }
    a[step].flag = 0;
}

void update(int step)
{
    a[step].sum1 = a[2 * step].sum1 + a[2 * step + 1].sum1;
    a[step].sum0 = a[2 * step].sum0 + a[2 * step + 1].sum0;
    if(a[2 * step].sum0) a[step].first = a[2 * step].first;
    else a[step].first = a[2 * step + 1].first;
}

void set1(int lt,int rt,int step)
{
    if(a[step].lt == lt && a[step].rt == rt) {
        a[step].sum0 = 0;
        a[step].sum1 = rt - lt + 1;
        a[step].flag = 1;
        a[step].first = -1;
        return;
    }
    if(a[step].flag) down(step);
    if(rt <= a[2 * step].rt) set1(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) set1(lt,rt,2 * step + 1);
    else {
        set1(lt,a[2 * step].rt,2 * step);
        set1(a[2 * step + 1].lt,rt,2 * step + 1);
    }
    update(step);
}

void set0(int lt,int rt,int step)
{
    if(a[step].lt == lt && a[step].rt == rt) {
        a[step].sum0 = rt - lt + 1;
        a[step].sum1 = 0;
        a[step].flag = 2;
        a[step].first = lt;
        return;
    }
    if(a[step].flag) down(step);
    if(rt <= a[2 * step].rt) set0(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) set0(lt,rt,2 * step + 1);
    else {
        set0(lt,a[2 * step].rt,2 * step);
        set0(a[2 * step + 1].lt,rt,2 * step + 1);
    }
    update(step);
}

void query(int lt,int rt,int step,int &sum0,int &sum1)
{
    if(lt > rt) {
        sum0 = sum1 = 0;
        return;
    }
    if(a[step].lt == lt && a[step].rt == rt) {
        sum0 = a[step].sum0;
        sum1 = a[step].sum1;
        return;
    }
    if(a[step].flag) down(step);
    if(rt <= a[2 * step].rt) query(lt,rt,2 * step,sum0,sum1);
    else if(lt > a[2 * step].rt) query(lt,rt,2 * step + 1,sum0,sum1);
    else {
        int sum01,sum02,sum11,sum12;
        query(lt,a[2 * step].rt,2 * step,sum01,sum11);
        query(a[2 * step + 1].lt,rt,2 * step + 1,sum02,sum12);
        sum0 = sum01 + sum02;
        sum1 = sum11 + sum12;
    }
}

int query_first(int lt,int rt,int step)
{
    if(a[step].lt == lt && a[step].rt == rt) return a[step].first;
    if(a[step].flag) down(step);
    if(rt <= a[2 * step].rt) return query_first(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) return query_first(lt,rt,2 * step + 1);
    else {
        int x = query_first(lt,a[2 * step].rt,2 * step);
        int y = query_first(a[2 * step + 1].lt,rt,2 * step + 1);
        if(x != -1) return x;
        return y;
    }
}

int query_last(int step,int k)
{
    if(a[step].lt == a[step].rt) return a[step].lt;
    if(a[step].flag) down(step);
    if(a[2 * step].sum0 >= k) return query_last(2 * step,k);
    else return query_last(2 * step + 1,k - a[2 * step].sum0);
}

int main()
{
    int cd,x,y,t,n,m,sum0,sum1;
    scanf("%d",&t);
    while(t --) {
        scanf("%d%d",&n,&m);
        init(0,n - 1,1);
        while(m --) {
            scanf("%d%d%d",&cd,&x,&y);
            if(cd == 2) {
                query(x,y,1,sum0,sum1);
                printf("%d\n",sum1);
                set0(x,y,1);
            }
            else {
                query(x,n - 1,1,sum0,sum1);
                if(!sum0 || y == 0) {
                    printf("Can not put any one.\n");
                    continue;
                }
                int ansx = query_first(x,n - 1,1);
                query(0,x - 1,1,sum0,sum1);
                int ansy = query_last(1,min(sum0 + y,a[1].sum0));
                set1(ansx,ansy,1);
                printf("%d %d\n",ansx,ansy);
            }
        }
        printf("\n");
    }
    return 0;
}

