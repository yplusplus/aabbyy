#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define rep(i,a,b) for(i = a; i <= b; i ++)
const int N = 200010;
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

char s[N],str[N],tmp[N];
int nxt[N],ex[N];
int nxt2[N],ex2[N];
int ans; 
void merge(int lt,int mid,int rt)
{
    if((rt - lt + 1) / 2 <= ans) return;
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
    for(int i = 0; i < len2; i ++) {
        int pos = len2 - i - 1;
        if(ex2[pos] >= i + 1) ans = max(ans,i + 1);
        if(i < 2) continue;
        pos ++;
        if(!ex[i]) continue;
        int up = min(i - 1,ex2[pos]);
        int down = max(1,i - ex[i]);
        if(up >= down) {
			ans = max(ans,i);
		}
    }
    
    strcpy(tmp,s);
    strcpy(s,str);
    strcpy(str,tmp);
    //swap(s,str);
    swap(len1,len2);
    ex_kmp(str,str,nxt,ex,len2,len2);
    reverse(s,s + len1);
    reverse(str,str + len2);
    ex_kmp(str,s,nxt2,ex2,len2,len1);
    for(int i = 2; i < len2; i ++) {
        int pos = len2 - i - 1;
        pos ++;
        if(!ex[i]) continue;
        int up = min(i - 1,ex2[pos]);
        int down = max(1,i - ex[i]);
        if(up >= down) {
			ans = max(ans,i);
		}
		//if(lt == 0 && rt == 6) cout << up << " " << down << " " << endl;	
    }
}

void solve(int st,int ed)
{
    if((ed - st + 1) / 2 <= ans) return;
    if(st >= ed) return;
    if(st + 1 == ed) {
        if(ss[st] == ss[ed])  ans = max(ans,1);
        return;
    }
    int mid = (st + ed) >> 1;
    merge(st,mid,ed);
    solve(st,mid);
    solve(mid + 1,ed);
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t --) {
		scanf("%s",ss);
        ans = 0;
        solve(0,strlen(ss) - 1);
        cout << ans << endl;
    }
    return 0;
}


