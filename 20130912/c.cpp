#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

const long long mod = 999983;

long long pow(long long a,long long b)
{
    long long ans = 1;
    a %= mod;
    while(b) {
        if(b & 1LL) ans = ans * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ans;
}

vector<int> init() {
    int r,x;
    scanf("%d",&r);
    vector<int> v;
    for(int i = 0; i <= r; i ++) {
        scanf("%d",&x);
        v.push_back(x);
    }
    reverse(v.begin(),v.end());
    return v;
}

//f(x) = g(x) * h(x) + r(x)，
//if x is a root of f(x) & g(x) ,f(x) = g(x) = 0,so x is a root of r(x)
vector<int> poly_mod(vector<int> a,vector<int> b)
{
    while(a.size() >= b.size()) {
        long long coe = 1LL * a.back() * pow(1LL * b.back(),mod - 2) % mod;
        for(int i = a.size() - 1, j = b.size() - 1; j >= 0; j --, i --) {
            a[i] = (a[i] - 1LL * b[j] * coe) % mod;
            if(a[i] < 0) a[i] += mod;
        }
        while(!a.empty() && !a.back()) a.pop_back();
    }
    return a;
}

vector<int> poly_gcd(vector<int> a,vector<int> b)
{
    vector<int> c;
    while(b.size()) {
        c = poly_mod(a,b);
        a = b;
        b = c;
    }
    return a;
}

bool solve(int n)
{
    vector<int> a,b;
    a = init();
    -- n;
    while(n --) {
        b = init();
        a = poly_gcd(a,b);
    }
    return a.size() > 1;
}

int main()
{
    int n;
    while(scanf("%d",&n) != EOF) {
        if(solve(n)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

