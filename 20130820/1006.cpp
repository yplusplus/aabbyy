#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define maxn 200010
int wa[maxn],wb[maxn],wv[maxn],wc[maxn];
int cmp(int *r,int a,int b,int l) {
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m) {
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++) wc[i]=0;
    for(i=0;i<n;i++) wc[x[i]=r[i]]++;
    for(i=1;i<m;i++) wc[i]+=wc[i-1];
    for(i=n-1;i>=0;i--) sa[--wc[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p) {
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) wc[i]=0;
        for(i=0;i<n;i++) wc[wv[i]]++;
        for(i=1;i<m;i++) wc[i]+=wc[i-1];
        for(i=n-1;i>=0;i--) sa[--wc[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}
int rank[maxn],height[maxn];
void calheight(int *r,int *sa,int n) {
     int i,j,k=0;
     for(i=1;i<=n;i++) rank[sa[i]]=i;
     for(i=0;i<n;height[rank[i++]]=k)
     for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
     return;
}

int RMQ[maxn];
int mm[maxn];
int best[20][maxn];
void initRMQ(int n) {
     int i,j,a,b;
     for(mm[0]=-1,i=1;i<=n;i++)
     mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
     mm[0] = 0;
     for(i=1;i<=n;i++) best[0][i]=height[i];
     for(i=1;i<=mm[n];i++)
         for(j=1; j <=n; j ++) {
             int temp = j + (1 << (i - 1));
             if(temp<=n) best[i][j] = min(best[i - 1][j],best[i - 1][temp]);
             else best[i][j]=best[i-1][j];
         }
}

int askRMQ(int a,int b) {
    int t;
    t=mm[b-a+1];b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return min(a,b);
}
int lcp(int a,int b) {
    a=rank[a];b=rank[b];
    if(a>b) swap(a, b);
    return askRMQ(a + 1,b);
}

char s[maxn];
int r[maxn];
int digit[100010],sa[maxn];

int get_digit(int x)
{
    int ans = 0;
    while(x) {
        ans ++;
        x /= 10;
    }
    return ans;
}

int main()
{
    digit[0] = 1;
    for(int i = 1; i < 100010; i ++) digit[i] = get_digit(i);
    int m;
    while(scanf("%s",s) != EOF) {
        long long ansx = 0,ansy = 0;
        int n = strlen(s);
        memset(sa,0,sizeof(sa));
        memset(height,0,sizeof(height));
        memset(r,0,sizeof(r));
        for(int i = 0; i < n; i ++)
            r[i] = s[i];
        da(r, sa, n + 1, 256);
        calheight(r, sa, n);    
        initRMQ(n + 2);
        scanf("%d",&m);
        int prex = -1,prey = -1,x,y;
        while(m --) {
            scanf("%d%d",&x,&y);
            ansx += y - x + 1;
            if(prex == -1) {
                ansy += y - x + 2;
                ansy += 1;
            }
            else {
                int lp;
                if(x == prex) lp = n - x;
                else lp = lcp(x,prex);
                lp = min(lp,min(y - x,prey - prex));
                ansy += y - x - lp;
                ansy += 2;
                ansy += digit[lp];
            }
            prex = x,prey = y;
        }
        printf("%I64d %I64d\n",ansx,ansy);
    }   
    return 0;
}

