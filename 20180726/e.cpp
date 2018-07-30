#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;

const int N = 2000010;
char s[N];
int hashs[2][N];
int keys[2] = {137, 10007};
int mods[2] = {1000000007, 1000000009};
int pows[2][N];

unordered_map<long long, int> mp;

long long encode(long long a, long long b) {
    return a * 1000000010 + b;
}

vector<int> v[N];
int rak[N];

bool cmp(int x, int y) {
    return v[x][0] < v[y][0];
}

int main()
{
    pows[0][0] = pows[1][0] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < 2; j++)
            pows[j][i] = 1LL * pows[j][i - 1] * keys[j] % mods[j];
    }

    while (scanf("%s", s) != EOF) {
        int n = strlen(s);
        for (int i = 0; i < n; i++) s[i + n] = s[i];
        int cnt = 0;
        for (int i = 0; i < (n << 1); i++) {
            for (int j = 0; j < 2; j++) {
                hashs[j][i + 1] = (hashs[j][i] + 1LL * s[i] * pows[j][i]) % mods[j];
            }

            int x = i - (n - 1);
            if (!(x >= 0 && x < n)) continue;
            long long val1 = hashs[0][i + 1] - hashs[0][i + 1 - n];
            if (val1 < 0) val1 += mods[0];
            long long val2 = hashs[1][i + 1] - hashs[1][i + 1 - n];
            if (val2 < 0) val2 += mods[1];

            val1 = val1 * pows[0][n - 1 - x] % mods[0];
            val2 = val2 * pows[1][n - 1 - x] % mods[1];
            long long id = encode(val1, val2);
            if (!mp.count(id)) {
                mp[id] = ++cnt;
                v[cnt].clear();
            }
            id = mp[id];
            v[id].push_back(x);

        }

        for (int i = 1; i <= cnt; i++) rak[i] = i;
        sort(rak + 1, rak + cnt + 1);
        printf("%d\n", cnt);
        for (int i = 1; i <= cnt; i++) {
            int x = rak[i];
            printf("%d", (int)v[x].size());
            for (int j = 0; j < v[x].size(); j++)
                printf(" %d", v[x][j]);
            printf("\n");
        }
    }
    return 0;
}
