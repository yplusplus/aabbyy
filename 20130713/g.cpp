#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(),(a).end()
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define FORD(i,a,b) for (int i=(a); i>=(b); i--)
#define REP(i,b) FOR(i,0,b)
#define ll long long
#define ull unsigned long long
#define sf scanf
#define pf printf
#define Maxn 111111
using namespace std;
const int maxint = -1u>>1;
const double pi = 3.14159265358979323;
const double eps = 1e-8;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;
typedef pair<ull, ull> puu;

const ull mod = 10570841;
const ull mod2 = 15485863;
const unsigned int key = 131;
const unsigned int key2 = 31;

char s1[Maxn], s2[Maxn];
int plen;
bool iodd;
//set<puu> vis;
puu hashcao[Maxn];
puu hashf[Maxn], hashb[Maxn];
map<puu, int> vis;
int n, m;

void calc(puu h[], char str[], int k, int len, bool iForward) {
    if (iForward) { 
        h[0].fi = 0; 
        h[0].se = 0;
        for (int i = 0; i < len; ++i) {
            h[0].fi = (h[0].fi * key + str[i] - 'a' + 1) % mod;
            h[0].se = (h[0].se * key2 + str[i] - 'a' + 1) % mod2;
        }
        ull t = 1, t2 = 1;
        REP(i, len-1) t = (t * key) % mod, t2 = (t2 * key2) % mod2;
        for (int i = 1; i < k; ++i) {
            h[i].fi = (h[i-1].fi + mod - t * (str[i-1]-'a'+1)%mod)%mod;
            h[i].fi = (h[i].fi * key + str[(i + len - 1)%k]-'a'+1) % mod;
            
            h[i].se = (h[i-1].se + mod2 - t2 * (str[i-1]-'a'+1)%mod2)%mod2;
            h[i].se = (h[i].se * key2 + str[(i + len - 1)%k]-'a'+1) % mod2;
        }
    }
    else {
        h[k-1].fi = 0;
        h[k-1].se = 0;
        for (int i = k - 1; i >= k - len; --i) {
            h[k-1].fi = (h[k-1].fi*key + str[i]-'a'+1) % mod;
            h[k-1].se = (h[k-1].se*key2 + str[i]-'a'+1) % mod2;
        }
        ull t = 1, t2 = 1;
        REP(i, len-1) t = (t * key) % mod, t2 = (t2 * key2) % mod2;
        //cout <<k <<" "<<k-len <<" " <<h[k-1] <<" "<<t <<endl;
        for (int i = k - 2; i >= 0; --i) {
            h[i].fi = (h[i+1].fi + mod - t * (str[i+1]-'a'+1)%mod) %mod;
            //cout <<h[i] <<" .... ";
            h[i].fi = (h[i].fi * key + str[(i - len + 1 + k) % k] - 'a' + 1) % mod;
            //cout <<h[i] <<endl;
            h[i].se = (h[i+1].se + mod2 - t2 * (str[i+1]-'a'+1)%mod2) %mod2;
            h[i].se = (h[i].se * key2 + str[(i - len + 1 + k) % k] - 'a' + 1) % mod2;
        }
    }
}

void init() {
    vis.clear();
    ull h1 = 0, h2 = 0, t1 = 1, t2 = 1;
    n = strlen(s1);
    m = strlen(s2);
    plen = (n - m + 1) / 2;
    iodd = (n - m) % 2 == 0 ? false : true;

    for (int i = m - 1; i >= 0; i--) {
        h1 = (h1 * key % mod + s2[i] - 'a' + 1) % mod;
        h2 = (h2 * key2 % mod2 + s2[i] - 'a' + 1) % mod2;
    }
    REP(i, m-1) t1 = (t1 * key) % mod, t2 = (t2 * key2) % mod2;
    
    //vis.insert(h1);
    //cout <<t1 <<endl;
    //cout <<"m string: " <<endl;
    //cout <<h1 <<" ";
    vis[mp(h1,h2)] = 0;
    for (int i = m - 2; i >= 0; i--) {
        h1 = (h1 + mod - t1 * (s2[i+1] - 'a' + 1) % mod) % mod;
        h1 = (h1 * key + s2[i+1] - 'a' + 1) % mod;
        h2 = (h2 + mod2 - t2 * (s2[i+1] - 'a' + 1) % mod2) % mod2;
        h2 = (h2 * key2 + s2[i+1] - 'a' + 1) % mod2;
        //vis.insert(h1);
        vis[mp(h1,h2)] = i + 1;
        //cout <<h1 <<" ";
    }
    //cout <<endl <<" -----------------------" <<endl;
    calc(hashcao, s1, n, m, true);
    calc(hashf, s1, n, plen, true);
    calc(hashb, s1, n, plen, false);
    //REP(i, n) cout <<hash[i] <<" ";
    //cout <<endl;
    
    //cout <<endl <<" -----------------------" <<endl;
    //REP(i, n) cout <<hashf[i] <<" ";
    //cout <<endl <<" -----------------------" <<endl;
    //REP(i, n) cout <<hashb[i] <<" ";
    //cout <<endl <<" -----------------------" <<endl;
}
pii solve() {
    
    //cout <<plen <<" : " <<iodd <<endl;
    REP(i, n) {
        if (iodd) {
            if (hashf[i] == hashb[i]) {
                if (vis.find(hashcao[(i+plen)%n]) != vis.end()) {
                    return mp((i+plen)%n, vis[hashcao[(i+plen)%n]]);
                }
            }
            else continue;
        }
        else {
            if (hashf[i] == hashb[(i-1+n)%n]) {
                int loc = (i + plen ) % n;
                if (vis.find(hashcao[loc]) != vis.end()) {
                    return mp(loc, vis[hashcao[loc]]);
                }
            }
            else continue;
        }
    }
    return mp(-1, -1);
}
int main() {
    while (~sf("%s", s1)) {
        sf("%s", s2);
        init();
        pii ans = solve();
        if (ans.fi < 0) puts("No");
        else {
            puts("Yes");
            pf("%d %d\n", ans.fi + 1, ans.se + 1);
        }
    }
    return 0;
}


