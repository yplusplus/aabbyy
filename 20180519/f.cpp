Code Render Status : Rendered By HDOJ G++ Code Render Version 0.01 Beta
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <cmath>
#include <cstdlib>
#include <map>
using namespace std;

const int N = 100010;
struct point {
    long long a[3];
    int id;
    void read(int _id) {
        id = _id;
        int x, y, z;
        //x = y = z = id;
        scanf("%d%d%d", &x, &y, &z);
        a[0] = x, a[1] = y, a[2] = z; 
        //scanf("%lld%lld%lld", &a[0], &a[1], &a[2]);
    }
}a[N];
/*
bool cmp(const point &p, const point &q) {
    long long a[6], b[6];
    int c1 = 0, c2 = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            a[c1++] = p.a[i] * q.a[j];
            b[c2++] = q.a[i] * p.a[j];
        }
    }
    unsigned long long dif = 0;
    int i = 0, j = 0;
    while (i < 6 && j < 6) {
        if (dif >= b[j]) dif -= b[j++];
        else if (dif + a[i] < b[j]) dif += a[i++];
        else dif = dif + a[i++] - b[j++];
    }
    while (j < 6 && dif >= b[j]) dif -= b[j++];

    if (j == 6) return false;
    return true;
}
*/

bool cmp(const point &a, const point &b) {
    unsigned long long x = 1ULL * a.a[2] * (b.a[0] + b.a[1] + b.a[2]);
    unsigned long long y =  1ULL * b.a[2] * (a.a[0] + a.a[1] + a.a[2]);
    if (x == y) return a.id  < b.id;
    return x > y;
    
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) a[i].read(i);
        sort(a + 1, a + n + 1, cmp);
        for (int i = 1; i <= n; i++) {
            printf("%d", a[i].id);
            if (i == n) printf("\n");
            else printf(" ");
        }
    }
    return 0;
}