#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
int cnt;
struct tree
{
    int a[N];
    int size,id;

    int lowbit(int x) { return x & (-x); }
    void init(int tid,int tsize) {
        size = tsize;
        id = tid;
        memset(a,0,sizeof(a));
    }
    void insert(int x,int y) {
        if(id == 1) x = cnt - x + 1;
        for(int i = x; i <= cnt; i += lowbit(i))
            a[i] = max(a[i],y);
    }
    int query(int x) {
        if(!(x >= 1 && x <= cnt)) return 0;
        if(id == 1) x = cnt - x + 1;
        int ans = 0;
        for(int i = x; i > 0; i -= lowbit(i))
            ans = max(ans,a[i]);
        return ans;
    }
}T[2];


int a[N],b[N];

int find(int x)
{
    int lt = 1,rt = cnt,mid;
    while(lt <= rt) {
        mid = (lt + rt) / 2;
        if(b[mid] == x) return mid;
        if(b[mid] > x) rt = mid - 1;
        else lt = mid + 1;
    }
}


void read(int &x)
{
    int flag = 1;
    char c;
    while(1) {
        c = getchar();
        if(isdigit(c) || c == '-') break;
    }
    if(c == '-') {
        flag = -1;
        x = 0;
    }
    else x = c - '0';
    while(1) {
        c = getchar();
        if(isdigit(c)) x = 10 * x + (c - '0');
        else break;
    }
    x *= flag;
}

int main()
{
    int t,n;
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++) {
            read(a[i]);
            b[i] = a[i];
        }
        int ans = 1;
        sort(b + 1,b + n + 1);
        cnt = 1;
        for(int i = 1 ; i <= n; i ++)
            if(b[i] != b[cnt]) b[++ cnt] = b[i];
        T[0].init(0,cnt);
        T[1].init(1,cnt);
        for(int i = n; i >= 1; i --) {
            a[i] = find(a[i]);
            int x1 = T[0].query(a[i] - 1);
            int y1 = T[1].query(a[i] + 1); //T[1].query(a[i],cnt,1);
            int x2 = T[0].query(a[i]);
            x2 = max(x2,x1); //T[0].query(1,a[i],1);
            int y2 = T[1].query(a[i]);
            y2 = max(y1,y2);
            int x = x1 + y2 + 1;
            int y = x2 + y1 + 1;
            ans = max(ans,max(x,y));
            x = x2 + 1;
            T[0].insert(a[i],x);
            x = y2 + 1;
            T[1].insert(a[i],x);
        }
        printf("%d\n",ans);
    }
    return 0;
}

