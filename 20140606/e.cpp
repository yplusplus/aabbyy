#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int max_id;
long long val[N];
char s[N];
int n,m;
int bits[1 << 13];
int mask,cnt;
int match[N];
int first_id,last_id;
long long a[13][13];
int sets[15];
long long tot[15];
int cc,maps[15];
long long sum[13][1 << 13];
long long ans;
long long zero;

void update(int &x,int &y,int xx,int yy)
{
    if(mask & (1 << x)) x = xx;
    if(!(mask & (1 << yy))) y = yy;
}

void dfs(int x,int y,long long a[13][13],int &first,int &last,long long &zero) 
{
    if(x == y) {
        first = last = val[x];
        if(mask & (1 << val[x])) zero = 1;
        return;
    }
    if(s[x] == 'V') {
        long long newa[13][13];
        memset(newa,0,sizeof(newa));
        int firsta,lasta;
        long long tzero = 0;
        dfs(x + 1,y,newa,firsta,lasta,tzero);
        for(int i = 0; i < max_id; i ++)
            for(int j = 0; j < max_id; j ++)
                a[i][j] = newa[i][j];
        first = last = val[x];
        if(!(mask & (1 << last))) {
            if(!(mask & (1 << firsta))) a[last][firsta] ++;
        }
        update(first,last,firsta,lasta);
        zero = tzero;
        if(mask & (1 << val[x])) zero ++;
    }
    else {
        long long newa[13][13];
        memset(newa,0,sizeof(newa));
        int firsta,lasta;
        long long tzero = 0;
        dfs(x + 1,match[x] - 1,newa,firsta,lasta,tzero);
        first = firsta,last = lasta;
        for(int i = 0; i < max_id; i ++)
            for(int j = 0; j < max_id; j ++)
                a[i][j] = newa[i][j] * val[x];
        zero = val[x] * tzero;
        if(!(mask & (1 << lasta))) {
           if(!(mask & (1 << firsta))) a[lasta][firsta] += val[x] - 1;
        }
        if(match[x] == y) return;
        memset(newa,0,sizeof(newa));
        tzero = 0;
        dfs(match[x] + 1,y,newa,firsta,lasta,tzero);
        zero += tzero;
        for(int i = 0; i < max_id; i ++)
            for(int j = 0; j < max_id; j ++)
                a[i][j] += newa[i][j];
        if(!(mask & (1 << last))) {
            if(!(mask & (1 << firsta))) a[last][firsta] ++;
        }
        update(first,last,firsta,lasta);
    }
}

void cal()
{
    long long tmp = zero;
    long long flag = 0;
    for(int i = 0; i < max_id; i ++) {
        if(mask & (1 << i)) continue;
        tmp += sum[i][sets[maps[i]]];
        tmp += 2 * (tot[i] - sum[i][sets[maps[i]]]);
        if(tot[i]) flag = 1;
    }
    ans = min(ans,tmp + flag * 2);
}

void dfs(int pos)
{
    if(cc > n) return;
    if(pos == max_id) {
        cal();
        return;
    }
    if(mask & (1 << pos)) {
        dfs(pos + 1);
        return;
    }
    for(int i = 1; i < cc; i ++) {
        if(bits[sets[i]] == m) continue;
        sets[i] ^= (1 << pos);
        maps[pos] = i;
        dfs(pos + 1);
        sets[i] ^= (1 << pos);
    }
    sets[cc] = (1 << pos);
    maps[pos] = cc ++;
    dfs(pos + 1);
    sets[-- cc] ^= (1 << pos);
}

void merge()
{
    cc = 1;
    memset(sum,0,sizeof(sum));
    memset(tot,0,sizeof(tot));
    memset(sets,0,sizeof(sets));
    sets[0] = mask;
    for(int i = 0; i < max_id; i ++) {
        if(mask & (1 << i)) {
            maps[i] = 0;
            continue;
        }
        for(int j = 0; j < max_id; j ++) {
            tot[i] += a[j][i];
        }
        for(int k = 0; k < (1 << max_id); k ++) {
            if(!(k & (1 << i))) continue;
            if(bits[k] > m) continue;
            for(int j = 0; j < max_id; j ++) {
                if(k & (1 << j)) sum[i][k] += a[j][i];
            }
        }
    }
    dfs(0);
}

void solve()
{
    gets(s);
    max_id = min(13,n * m);
    char c,str[110];
    cnt = 0;
    while(1) {
        c = getchar();
        if(c == '\n') break;
        if(c == 'V' || c == 'R' || c == 'E') {
            cin.putback(c);
            scanf("%s",str);
            val[cnt] = 0;
            s[cnt] = str[0];
            for(int i = 1; str[i]; i ++)
                val[cnt] = val[cnt] * 10 + (str[i] - '0');
            if(str[0] == 'V') val[cnt] --;
            if(str[0] == 'R') assert(val[cnt] != 0);
            cnt ++;
        }
    }
    for(int i = 0; i < cnt; i ++) {
        if(s[i] != 'R') continue;
        for(int j = i,tot = 0; j < cnt; j ++) {
            if(s[j] == 'R') tot ++;
            else if(s[j] == 'E') tot --;
            if(tot == 0) {
                match[i] = j;
                break;
            }
        }
    }
    ans = 1LL << 62;
    for(mask = 0; mask < (1 << max_id); mask ++) {
        if(bits[mask] != m) continue;
        memset(a,0,sizeof(a));
        zero = 0;
        dfs(0,cnt - 1,a,first_id,last_id,zero);
        merge();
        //cout << mask << " " << zero << endl;
        //for(int i = 0; i < max_id; i ++) {
            //for(int j = 0; j < max_id; j ++)
                //cout << a[i][j] << " ";
            //cout << endl;
        //}
        //cout << ans << endl;
        //cout << endl;
    }
    cout << ans << endl;
}

int main()
{
    for(int i = 0; i < (1 << 13); i ++)
        for(int j = 0; j < 13; j ++)
            if(i & (1 << j)) bits[i] ++;
    while(scanf("%d%d",&n,&m) != EOF) {
        solve();
    }
    return 0;
}

