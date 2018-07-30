#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e7 + 5;

int np, p[N / 10];
bool vis[N];

void Init()
{
    np = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i < N; i++) {
        if (!vis[i]) p[np ++] = i;
        for (int j = 0; j < np && i * p[j] < N; j++) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
}

int FindP(int k)
{
    int l = 0, r = np - 1, ret = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (p[mid] <= k) {
            ret = mid;
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return ret;
}

int main()
{
    Init();
    int n;
    while (cin >> n) {
        LL ret = 0;
        for (int i = np - 1; i >= 0; ) {
            int num = n / p[i];
            int nx_p = n / (num + 1);
            int nx_i = FindP(nx_p);

            LL sum = 1LL * (nx_i + 1 + i) * (i - nx_i) >> 1;
            ret += sum * num;

            i = nx_i;
        }
        ret <<= 1;
        cout << ret << endl;
    }
    return 0;
}
