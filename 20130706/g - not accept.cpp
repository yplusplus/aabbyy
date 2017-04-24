#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 25;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 55;
const int R = 9;
const int MAX = 22222;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int stone[MAX];
char maz[N][N];
int cost[1 << R], gain[1 << R];
int n, m, r, target;
int v[N][N], visit[N][N];
int X[R], Y[R], s[R];
int dist[R][R];

bool canGo(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maz[x][y] != 'X';
}

void bfs(int s) {
    queue<int> que;
    memset(visit, -1, sizeof(visit));
    int x = X[s], y = Y[s];
    que.push(x), que.push(y);
    visit[x][y] = 0;
    while (!que.empty()) {
        x = que.front(), que.pop();
        y = que.front(), que.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (canGo(nx, ny) && visit[nx][ny] == -1) {
                visit[nx][ny] = visit[x][y] + 1;
                que.push(nx), que.push(ny);
            }
        }
    }
    for (int i = 0; i <= r; i++) {
        x = X[i], y = Y[i];
        if (visit[x][y] == -1) dist[s][i] = dist[i][s] = inf;
        else dist[s][i] = dist[i][s] = visit[x][y];
    }
}

void detect() {
    for (int i = 0; i < r; i++) {
        bfs(i);
    }
    int a[R], tot;
    memset(gain, 0, sizeof(gain));
    cost[0] = 0;
    for (int mask = 1; mask < (1 << r); mask++) {
        cost[mask] = inf;
        tot = 0;
        for (int i = 0; i < r; i++) {
            if (mask >> i & 1) {
                gain[mask] += s[i];
                a[tot++] = i;
            }
        }
        do {
            int pre = r;
            int tmp = 0;
            for (int i = 0; i < tot; i++) {
                tmp += dist[pre][a[i]];
                pre = a[i];
                if (tmp >= cost[mask]) break;       
            }
            cost[mask] = min(cost[mask], tmp);
        } while (next_permutation(a, a + tot));
    }
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &target)) {
        for (int i = 0; i < n; i++) scanf("%s", maz[i]);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &v[i][j]);
            }
        }
        scanf("%d", &r);
        for (int i = 0; i < r; i++) {
            scanf("%d%d%d", &X[i], &Y[i], &s[i]);
            X[i]--, Y[i]--;
        }
        scanf("%d%d", &X[r], &Y[r]);
        X[r]--, Y[r]--;

        detect();

        int ans = -1;
        pii myLand[N * N];
        int head = 0, tail = 0;
        priority_queue<int, vector<int>, less<int> > pq;
        memset(visit, 0, sizeof(visit));
        memset(stone, 0, sizeof(stone));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (maz[i][j] == '*') {
                    myLand[tail++] = mp(i, j);
                    visit[i][j] = 1;
                    if (v[i][j] > 0) pq.push(v[i][j]);
                }
            }
        }

        for (int i = 0; i < MAX; i++) {
            if (i > 0) stone[i] += stone[i - 1];

            int tmp = 0;
            for (int mask = 0; mask < (1 << r); mask++) {
                if (cost[mask] <= i * 2) {
                    tmp = max(tmp, gain[mask]);
                }
            }


            if (i && stone[i - 1] + tmp >= target) {
                ans = i;
                break;
            }

            if (i % 5 == 0) {
                if (i > 0) {
                    int newTail = tail;
                    for (int j = head; j < tail; j++) {
                        int x = myLand[j].fi, y = myLand[j].se;
                        for (int k = 0; k < 4; k++) {
                            int nx = x + dx[k], ny = y + dy[k];
                            if (canGo(nx, ny) && !visit[nx][ny]) {
                                visit[nx][ny] = 1;
                                myLand[newTail++] = mp(nx, ny);
                                if (v[nx][ny] > 0) pq.push(v[nx][ny]);
                            }
                        }
                    }
                    head = tail;
                    tail = newTail;
                }
                
                if (!pq.empty()) {
                    tmp = pq.top(), pq.pop();
                    for (int j = 0; j < tmp; j++) {
                        stone[i + j] += tmp - j;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
