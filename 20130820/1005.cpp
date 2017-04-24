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
const double pi = 3.14159265358979323;
const double eps = 1e-8;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

int asc[] = {0,1,2,3,0,9,0,127,0,0,0,11,12,13,14,15,16,17,18,19,0,0,8,0,24,25,0,0,28,29,30,31,0,0,0,0,0,10,23,27,0,0,0,0,0,5,6,7,0,0,22,0,0,0,0,4,0,0,0,0,20,21,0,26,32,0,0,0,0,0,0,0,0,0,0,46,60,40,43,124,38,0,0,0,0,0,0,0,0,0,33,36,42,41,59,0,45,47,0,0,0,0,0,0,0,0,0,44,37,95,62,63,0,0,0,0,0,0,0,0,0,96,58,35,64,39,61,34,0,97,98,99,100,101,102,103,104,105,0,0,0,0,0,0,0,106,107,108,109,110,111,112,113,114,0,0,0,0,0,0,0,126,115,116,117,118,119,120,121,122,0,0,0,0,0,0,94,0,0,0,0,0,0,0,0,0,91,93,0,0,0,0,123,65,66,67,68,69,70,71,72,73,0,0,0,0,0,0,125,74,75,76,77,78,79,80,81,82,0,0,0,0,0,0,92,0,83,84,85,86,87,88,89,90,0,0,0,0,0,0,48,49,50,51,52,53,54,55,56,57,0,0,0,0,0,0};

map<string,int> id;
void init() {
    memset(asc, 0, sizeof(asc));
    id.clear();
    string s;
    for (int i = 0; i <= 7; i++ ) {
        for (int j = 0; j <= 15; j++) {
            cin >>s;
            id[s] =  i * 16 + j;
        }
    }
    cout <<id.size() <<endl;
    for (int i = 0; i < 16; i++) {
        REP(j, 16) {
            cin >>s;
            if (s.size() <= 2) continue;
            asc[i * 16 + j] = id[s.substr(2)];
        }
    }
    cout <<"{";
    REP(i, 16*16) cout <<asc[i] <<",";
}


int main() {
    //freopen("a.txt", "r", stdin);
    //freopen("b.txt", "w", stdout);
    //init();
    int x;
    while (~sf("%2X", &x)) {
        pf("%02X", asc[x]);
    }
    puts("");
    return 0;
}

