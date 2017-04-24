#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define rep(i,a,b) for(i = a; i <= b; i ++)
const int N = 500010;
char ss[N];

void ex_kmp(char *s,char *str,int nxt[],int ex[],int lena,int lenb)
{
    nxt[0] = lenb,nxt[1] = lenb - 1;
    int i, j, k = 1,p, L;
    rep(i,0,lenb - 2) if(str[i] != str[i + 1]) {
       nxt[1] = i;
       break;
    } 
    rep(i,2,lenb - 1) {
        p = k + nxt[k] - 1;
        L = nxt[i - k];
        if(i + L <= p) nxt[i] = L;
        else {
            j = p - i + 1;
            if(j < 0) j = 0;
            while(i + j < lenb && str[i + j] == str[j]) j ++;
            nxt[i] = j;
            k = i;
        }     
    }
    int minlen = lena >= lenb ? lena : lenb;
    ex[0] = minlen;
    rep(i,0,minlen - 1) if(s[i] != str[i]) {
        ex[0] = i;
        break;
    }
    k = 0;
    rep(i,1,lena - 1) {
        p = k + ex[k] - 1, L = nxt[i - k];
        if(i + L <= p) ex[i] = L;
        else {
            j = p - i + 1;
            if(j < 0) j = 0;
            while(i + j < lena && j < lenb && s[i + j] == str[j]) j ++;
            ex[i] = j;
            k = i;
        }
    }
}

struct BIT
{
    int a[N];
    int lowbit(int x) { return x & (-x); }
    void clear() { memset(a,0,sizeof(a)); }
    void insert(int x,int y) { 
        for(int i = x; i < N; i += lowbit(i)) a[i] += y; 
    }
    void add(int x,int y) { 
        insert(x,1),insert(y + 1,-1); 
        //cout << x << " " << y << endl;
    }
    int query(int x) { long long ans = 0; for(int i = x; i > 0; i -= lowbit(i)) ans += a[i]; return ans > 0 ? 1 : 0; }
}bit;

char s[N],str[N],tmp[N];
int nxt[N],ex[N];
int nxt2[N],ex2[N];
int n;

void merge(int lt,int mid,int rt)
{
    for(int i = lt; i <= mid; i ++) {
        s[i - lt] = ss[i];
    }
    int len1 = mid - lt + 1;
    s[len1] = 0;
    for(int i = mid + 1; i <= rt; i ++) {
        str[i - mid - 1] = ss[i];
    }
    int len2 = rt - mid;
    str[len2] = 0;
    ex_kmp(str,str,nxt,ex,len2,len2);
    reverse(s,s + len1);
    reverse(str,str + len2);
    ex_kmp(str,s,nxt2,ex2,len2,len1);
    for(int i = 0; i < len2 && i < n - 1; i ++) {
        int pos = len2 - i - 1;
        if(ex2[pos] >= i + 1) bit.add(mid + 1,mid + 1);
        if(!ex2[pos]) continue;
        if(i < 1) continue;
        if(i == len2 - 1) continue;
        if(!ex[i + 1]) continue;
        int x = max(1,i + 1 - ex2[pos]);
        int y = min(i,ex[i + 1]);
        if(x <= y) bit.add(x + mid + 1,y + mid + 1);
    }
    
    
    strcpy(tmp,s);
    strcpy(s,str);
    strcpy(str,tmp);
    swap(len1,len2);
    ex_kmp(str,str,nxt,ex,len2,len2);
    reverse(s,s + len1);
    reverse(str,str + len2);
    ex_kmp(str,s,nxt2,ex2,len2,len1);
    for(int i = 1; i < len2 && i < n - 1; i ++) {
        int pos = len2 - i - 1;
        if(!ex2[pos]) continue;
        if(!ex[i + 1]) continue;
        if(i == len2 - 1) continue;
        int x = max(1,i + 1 - ex2[pos]);
        int y = min(i,ex[i + 1]);
        if(x <= y) bit.add(mid - y + 1,mid - x + 1);
    }
}

void solve(int st,int ed)
{
    if(st >= ed) return;
    if(st + 1 == ed) {
        if(ss[st] == ss[ed])  bit.add(ed,ed);
        return;
    }
    int mid = (st + ed) >> 1;
    merge(st,mid,ed);
    solve(st,mid);
    solve(mid + 1,ed);
}

int main()
{
    freopen("border.in","r",stdin);
    freopen("border.out","w",stdout);
    bit.clear();
    scanf("%s",tmp);
    strcpy(ss,tmp);
    strcat(ss,tmp);
    strcat(ss,tmp);
    n = strlen(tmp);
    if(n == 1) {
        puts("0");
        return 0;
    }
    solve(0,3 * n - 1);
    for(int i = 0; i < n; i ++)
        if(bit.query(i + n)) putchar('1');
        else putchar('0');
    puts("");
    return 0;
}



