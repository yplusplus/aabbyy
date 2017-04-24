#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;

const int N = 100010;
const long long oo = 1LL << 50;
struct node
{
    int lt,rt;
    long long val,flag,mx1,mx2;
};

struct tree
{
    node a[N * 4];
    void init(int lt,int rt,int step) {
        a[step].lt = lt;
        a[step].rt = rt;
        a[step].flag = oo;
        a[step].mx1 = a[step].mx2 = oo;
        a[step].val = 1LL << 50;
        if(lt == rt) return;
        int mid = (lt + rt) / 2;
        init(lt,mid,2 * step);
        init(mid + 1,rt,2 * step + 1);
    }
    
    void down(int step) {
        a[2 * step].flag = a[step].flag;
        a[2 * step + 1].flag = a[step].flag;
        a[2 * step].mx1 = a[2 * step].mx2 + a[step].flag;
        a[2 * step + 1].mx1 = a[2 * step + 1].mx2 + a[step].flag;
        a[step].flag = oo;
    }
    
    void insert(int pos,int step,long long val) {
        if(a[step].lt == a[step].rt) {
            a[step].val = val;
            a[step].mx1 = a[step].val + a[step].flag;
            a[step].mx2 = a[step].val;
            return;
        }
        if(a[step].flag != oo) down(step);
        if(pos <= a[2 * step].rt) insert(pos,2 * step,val);
        else insert(pos,2 * step + 1,val);
        a[step].mx1 = min(a[2 * step].mx1,a[2 * step + 1].mx1);
        a[step].mx2 = min(a[2 * step].mx2,a[2 * step + 1].mx2);        
    }
    
    void insert(int lt,int rt,int step,int x) {
        if(a[step].lt == lt && a[step].rt == rt) {
            a[step].flag = x;
            a[step].mx1 = a[step].mx2 + x;
            return;
        }
        if(a[step].flag != oo) down(step);
        if(rt <= a[2 * step].rt) insert(lt,rt,2 * step,x);
        else if(lt > a[2 * step].rt) insert(lt,rt,2 * step + 1,x);
        else {
            insert(lt,a[2 * step].rt,2 * step,x);
            insert(a[2 * step + 1].lt,rt,2 * step + 1,x);
        }
        a[step].mx1 = min(a[2 * step].mx1,a[2 * step + 1].mx1);
        a[step].mx2 = min(a[2 * step].mx2,a[2 * step + 1].mx2);
    }   
    
    long long query(int lt,int rt,int step) {
        if(a[step].lt == lt && a[step].rt == rt) return a[step].mx1;
        if(a[step].flag != oo) down(step);
        if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
        else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
        else {
            long long x = query(lt,a[2 * step].rt,2 * step);
            long long y = query(a[2 * step + 1].lt,rt,2 * step + 1);
            return min(x,y);
        }
    }
}T;

int a[N],b[N],pre[N * 10],map[N * 10];
stack<int> sta;
int lt[N],rt[N];

void init(int n)
{
    while(!sta.empty()) sta.pop();
    memset(map,-1,sizeof(map));
    for(int i = 1; i <= n; i ++) {
        pre[i] = map[a[i]];
        map[a[i]] = i;
    }
    b[0] = b[n + 1] = 1000000000;
    for(int i = 1; i <= n; i ++) {
        lt[i] = i;
        while(b[i] >= b[lt[i] - 1])
            lt[i] = lt[lt[i] - 1];
    }
    for(int i = n; i >= 1; i --) {
        rt[i] = i;
        while(b[i] >= b[rt[i] + 1]) {
            rt[i] = rt[rt[i] + 1];
        }
    }
}

long long dp[N];
void process(int n)
{
//    cout << "enter" << endl;
    T.init(0,n + 2,1);
//    cout << "no" << endl;
    dp[0] = 0;
    T.insert(1,1,1,0);
//    cout << 2 << endl;
    T.insert(1,1,0LL);
   // for(int i = 1; i <= n; i ++) cout << pre[i] << " ";
    //cout << endl;
//    cout << "yes" << endl;
    //insert(int pos,int step,long long val)
    //insert(int lt,int rt,int step,int x)
    //long long query(int lt,int rt,int step)
    for(int i = 1; i <= n; i ++) {
        int pos = lt[i];
        if(pre[i] == -1) pre[i] = 0;
        T.insert(lt[i],rt[i],1,b[i]);
        dp[i] = T.query(pre[i] + 1,i,1);
        T.insert(i + 1,1,dp[i]);
        //cout << i << endl;
    }
    /*
    for(int i = 1; i <= n; i ++) cout << dp[i] << " ";
    cout << endl;*/
    cout << dp[n] << endl;   
}

int main()
{
    int t,n;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++) scanf("%d",&a[i]);
        for(int i = 1; i <= n; i ++) scanf("%d",&b[i]);
        init(n);
        process(n);   
    }
    return 0;
}

