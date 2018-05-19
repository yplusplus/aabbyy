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

const int N = 10100;
char s[N], str[N];

int main()
{
    while (scanf("%s%s", s, str) != EOF) {
        vector<int> va, vb;
        int n = strlen(s);
        for (int i = 0; i < n; i++) {
            if (s[i] == 'c') {
                va.push_back(i);
            }
        }
        int m = strlen(str);
        for (int i = 0; i < m; i++) {
            if (str[i] == 'c') vb.push_back(i);
        }
        if (va.size() != vb.size()) {
            printf("No\n");
            continue;
        }
        bool flag = true;
        va.push_back(n);
        vb.push_back(m);
        for (int i = 0; i < va.size(); i++) {
            int sta = 0, stb = 0;
            if (i > 0) sta = va[i - 1] + 1, stb = vb[i - 1] + 1;
            int xa = 0, xb = 0, ya = 0, yb = 0;
            for (int j = sta; j < va[i]; j++) {
                if (s[j] == 'a') xa ^= 1;
                else xb ^= 1;
            }
            for (int j = stb; j < vb[i]; j++) {
                if (str[j] == 'a') ya ^= 1;
                else yb ^= 1;
            }
            if (xa == ya && xb == yb) continue;
            flag = false;
        }
        if (flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}