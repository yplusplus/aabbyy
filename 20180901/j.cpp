#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;

const int N = 20000010;
int sum[N];
bool visit[N];
int prime[N];

void init() {
    sum[1] = 1;
    int tot = 0;
    for (int i = 2; i < N; i++) {
        if (!visit[i]) {
            sum[i] = 2;
            prime[tot++] = i;
        }
        for (int j = 0; j < tot && i * prime[j] < N; j++) {
            int x = i * prime[j];
            visit[x] = 1;
            if (i % prime[j]) {
                sum[x] = 2 * sum[i];
            } else if ((i / prime[j]) % prime[j] == 0) {
                sum[x] = 0;
                break;
            } else {
                sum[x] = sum[i / prime[j]];
                break;
            }
        }
    }
    for (int i = 1; i < N; i++) sum[i] += sum[i - 1];
}

int main()
{
    init();
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", sum[n]);
    }
    return 0;
}
