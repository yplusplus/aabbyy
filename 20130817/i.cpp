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
#define sf scanf
#define pf printf
using namespace std;
const int maxint = -1u>>1;
const int inf = 1<<29;
const double pi = 3.14159265358979323;
const double eps = 1e-8;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

int num;
string s, tar;
map<char,int> rom;
map<int,string> dig;
void init() {
    rom['I'] = 1; dig[1] = "I";
    rom['V'] = 5; dig[5] = "V";
    rom['X'] = 10; dig[10] = "X";
    rom['L'] = 50; dig[50] = "L";
    rom['C'] = 100; dig[100] = "C";
    rom['D'] = 500; dig[500] = "D";
    rom['M'] = 1000; dig[1000] = "M";
    
}
string makeReal(int x) {
    string ret;
    for (int i = 1; i <= x; i *= 10) {
        int k = (x / i) % 10;
        if (!k) continue;
        if (k < 4) {
            ret = string(k, dig[i][0]) + ret;
        }
        else if (k == 4) {
            ret = dig[i] + dig[i * 5] + ret;
        }
        else if (k == 5) {
            ret = dig[i * 5] + ret;
        }
        else if (k > 5 && k < 9) {
            ret = dig[i * 5] + string(k - 5, dig[i][0]) + ret;
        }
        else if (k == 9) {
            ret = dig[i] + dig[i * 10] + ret;
        }
        //cout <<k <<" --- "<<ret <<endl;
    }
    return ret;
}

pii ans;
pii calc(int st) {
    int e = st > 0 ? st : 0, c = 0;
    //cout <<"********" <<st <<endl;
    for (int i = st, j = 0; i < (int)s.length() || j < (int)tar.length(); i++, j++) {
        if (i < 0 || i >= (int)s.length()) c++;
        else if (j >= (int)tar.length()) e++;
        else if (s[i] != tar[j]) e++, c++;
        //cout <<i <<" "<<j <<" : " <<e <<" "<<c <<endl;
    }
    return mp(e, c);
}
void solve() {
    ans = mp(inf, inf);
    int st = tar.length();
    for (int i = -st; i <= (int)s.length(); i++) {
        pii tmp = calc(i);
        //cout <<i <<" "<<tmp.fi <<" "<<tmp.se <<endl;
        if (tmp.fi + tmp.se < ans.fi + ans.se || (tmp.fi + tmp.se == ans.fi + ans.se && tmp < ans)) ans = tmp;
    }
    cout <<ans.fi <<" "<<ans.se <<endl;
}
int main() {
    ios::sync_with_stdio(false);
    init();
    while (cin >>s) {
        if (s == "*") break;
        num = 0;
        REP(i, s.size()) 
            num += rom[s[i]];
        
        tar = makeReal(num);
        //cout <<tar <<" "<<num <<endl;
        solve();
    }
    return 0;
}


