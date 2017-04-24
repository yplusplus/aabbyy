#include <bits/stdc++.h>
using namespace std;

double sqr(double x)
{
    return x * x;
}

int main()
{
    int t;
    double x,y,r;
    cin >> t;
    while(t --) {
        cin >> x >> y >> r;
        printf("%.2lf %.2lf\n", r - sqrt(sqr(x) + sqr(y)), r + sqrt(sqr(x) + sqr(y)));
    }
    return 0;
}

