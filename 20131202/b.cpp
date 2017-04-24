#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
struct tree
{
    int lt,rt,mx[2],flag;
}a[N * 4];

int c[N],LEN;
void init(int lt,int rt,int step)
{
    a[step].lt = lt;
    a[step].rt = rt;
    a[step].flag = 0;
    if(lt == rt) {
        if(c[lt] == -1) a[step].mx[0] = a[step].mx[1] = -1;
        else {
            a[step].mx[0] = c[lt];
            a[step].mx[1] = LEN - c[lt];
        }
        return;
    }
    int mid = (lt + rt) / 2;
    init(lt,mid,2 * step);
    init(mid + 1,rt,2 * step + 1);
    a[step].mx[0] = max(a[2 * step].mx[0],a[2 * step + 1].mx[0]);
    a[step].mx[1] = max(a[2 * step].mx[1],a[2 * step + 1].mx[1]);
}

void down(int step)
{
    a[2 * step].flag ^= 1;
    a[2 * step + 1].flag ^= 1;
    
    swap(a[2 * step].mx[0],a[2 * step].mx[1]);
    swap(a[2 * step + 1].mx[0],a[2 * step + 1].mx[1]);
    a[step].flag = 0;
}

int query(int lt,int rt,int step)
{
    if(a[step].lt == lt && a[step].rt == rt) return a[step].mx[0];
    if(a[step].flag) down(step);
    if(rt <= a[2 * step].rt) return query(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) return query(lt,rt,2 * step + 1);
    else return max(query(lt,a[2 * step].rt,2 * step),query(a[2 * step + 1].lt,rt,2 * step + 1));
}

void reverse(int lt,int rt,int step)
{
    if(a[step].lt == lt && a[step].rt == rt) {
        swap(a[step].mx[0],a[step].mx[1]);
        a[step].flag ^= 1;
        return;
    }
    if(a[step].flag) down(step);
    if(rt <= a[2 * step].rt) reverse(lt,rt,2 * step);
    else if(lt > a[2 * step].rt) reverse(lt,rt,2 * step + 1);
    else {
        reverse(lt,a[2 * step].rt,2 * step);
        reverse(a[2 * step + 1].lt,rt,2 * step + 1);
    }
    a[step].mx[0] = max(a[2 * step].mx[0],a[2 * step + 1].mx[0]);
    a[step].mx[1] = max(a[2 * step].mx[1],a[2 * step + 1].mx[1]);    
}

void insert(int pos,int step,int val)
{
    if(a[step].lt == a[step].rt) {
        a[step].mx[0] = val;
        a[step].mx[1] = LEN - val;
        return;
    }
    if(a[step].flag) down(step);
    if(pos <= a[2 * step].rt) insert(pos,2 * step,val);
    else insert(pos,2 * step + 1,val);
    a[step].mx[0] = max(a[2 * step].mx[0],a[2 * step + 1].mx[0]);
    a[step].mx[1] = max(a[2 * step].mx[1],a[2 * step + 1].mx[1]);    
}

int b[N],pre[N],nxt[N];
int lowbit(int x)
{
    return x & (-x);
}

void binsert(int x,int y)
{
    for(int i = x; i < N; i += lowbit(i))
        b[i] += y;
}

int bquery(int x)
{
    int ans = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        ans += b[i];
    return ans;
}

bool check(char a,char b)
{
    return max(a,b) - 32 == min(a,b);
}

char change(char c)
{
    if(c >= 'A' && c <= 'Z') return c + 32;
    return c - 32;
}
    
bool solve()
{
    int n,x,y;
    char s[15],str[N];
    if(scanf("%d%s",&n,s) == EOF) return false;
    LEN = strlen(s);
    scanf("%s",str + 1);
    int m = strlen(str + 1);
    memset(b,0,sizeof(b));
    memset(pre,-1,sizeof(pre));
    memset(nxt,-1,sizeof(nxt));
    for(int i = 1; i <= m; i ++) {
        if(i + LEN - 1 > m) {
            c[i] = -1;
            continue;
        }
        int match = 0;
        for(int j = 0; j < LEN; j ++) {
            if(str[i + j] == s[j]) continue;
            else {
                if(check(s[j],str[i + j])) match ++;
                else {
                    match = -1;
                    break;
                }
            }
        }
        c[i] = match;
    }
    init(1,m,1);
    for(int i = 1; i <= m; i ++)
        if(c[i] != -1) pre[i] = i;
        else pre[i] = pre[i - 1];
    for(int i = m; i >= 1; i --) {
        if(c[i] != -1) nxt[i] = i;
        else nxt[i] = nxt[i + 1];
    }
    while(n --) {
        scanf("%d%d",&x,&y);
        binsert(x,1);        
        binsert(y + 1,-1);        
        if(y - x + 1 < LEN) {
            printf("-1\n");
        }
        else {
            int ans = query(x,y - LEN + 1,1);
            printf("%d\n",ans);
            if(ans != -1) {
                reverse(x,y - LEN + 1,1);
            }
        }
        for(int i = max(1,x - LEN + 1); i < x && i + LEN - 1 <= m; i ++) {
            if(c[i] == -1) continue;
            int match = 0;
            for(int j = 0; j < LEN; j ++) {
                char tmp = str[i + j];
                if(bquery(i + j) & 1) tmp = change(tmp);
                if(tmp == s[j]) continue;
                else match ++;
            }
            insert(i,1,match);
        }
        for(int i = max(1,y - LEN + 2); i <= y && i + LEN - 1 <= m; i ++) {
            if(c[i] == -1) continue;
            int match = 0;
            for(int j = 0; j < LEN; j ++) {
                char tmp = str[i + j];
                if(bquery(i + j) & 1) tmp = change(tmp);
                if(tmp == s[j]) continue;
                else match ++;
            }
            insert(i,1,match);            
        }
            
    }
    return true;
}

int main()
{
    while(solve());
    return 0;
}
/*
3 gR
PrOgRAMmINgiSgrEAt
1 7
4 18
6 14
9 abCAb
aBcAbCAbaBCAb
1 13
1 13
4 8
5 11
3 11
4 10
1 13
8 8
1 13
*/

