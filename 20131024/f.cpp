#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2000010;
int wa[N],wb[N],wv[N],wss[N];

int cmp(int *r,int a,int b,int len)
{
    return r[a] == r[b] && r[a + len] == r[b + len];
}

void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x = wa,*y = wb,*t;
    for(i = 0; i < m; i ++) wss[i] = 0;
    for(i = 0; i < n; i ++) wss[x[i] = r[i]] ++;
    for(i = 1; i < m; i ++) wss[i] += wss[i - 1];
    for(i = n - 1; i >= 0; i --) sa[-- wss[x[i]]] = i;
    for(j = p = 1; p < n; j *= 2,m = p) {
        for(p = 0, i = n - j; i < n; i ++) y[p ++] = i;
        for(i = 0; i < n; i ++) if(sa[i] >= j) y[p ++] = sa[i] - j;
        for(i = 0; i < n; i ++) wv[i] = x[y[i]];
        for(i = 0; i < m; i ++) wss[i] = 0;
        for(i = 0; i < n; i ++) wss[wv[i]] ++;
        for(i = 1; i < m; i ++) wss[i] += wss[i - 1];
        for(i = n - 1; i >= 0; i --) sa[-- wss[wv[i]]] = y[i];
        for(t = x,x = y,y = t,p = 1,x[sa[0]] = 0, i = 1; i < n; i ++)
            x[sa[i]] = cmp(y,sa[i - 1],sa[i],j) ? p - 1 : p ++;
    }
}

int rak[N],height[N];
void calheight(int *r,int *sa,int n)
{
    int i,j,k = 0;
    for(i = 1; i < n; i ++) rak[sa[i]] = i;
    for(i = 0; i < n - 1; height[rak[i ++]] = k)
        for(k ? k -- : 0, j = sa[rak[i] - 1]; r[i + k] == r[j + k]; k ++);
}

int r[N],sa[N];

bool check(char c)
{
    return c >= 'a' && c <= 'z';
}

long long solve(int len)
{
    memcpy(sa,r,sizeof(r));
    memset(r,0,sizeof(r));    
    long long ans = 0;
    for(int i = 0; i < len ; i ++) {
        if(sa[i] != '@') continue;
        long long y = 0,pos = i;
        for(int j = i + 1; j < len; j ++) {
            if(check(sa[j])) {
                y ++;
            }
            else if(sa[j] == '.') {
                if(!y) break;
                if(sa[j - 1] == '.') break;
            }
            else break;
            r[j] = y;
            pos = j;
        }
        if(!y) continue;
        long long x = 0;
        for(int j = i - 1; j >= 0; j --) {
            if(sa[j] == '.') {
                if(!x) break;
                if(sa[j + 1] == '.') break;
            }
            else if(check(sa[j])) {
                if(j + height[rak[j]] - 1 <= pos) ans += y - r[max(i,j + height[rak[j]] - 1)];
                x ++;
            }
            else break;
        }
    }
    return ans;
}
            
int main()
{
    int len = 0;
    memset(r,0,sizeof(r));
    memset(sa,0,sizeof(sa));
    memset(rak,0,sizeof(rak));
    memset(height,0,sizeof(height));
    char c;
    while((c = getchar()) != EOF) {
        r[len ++] = c;
        if(!(c >= 32 && c <= 126)) r[len - 1] = 1;
        if(len > 1500000) return 0;
    }
    da(r,sa,len + 1,2000000);
    calheight(r,sa,len + 1);
    cout << solve(len) << endl;
    return 0;
}





