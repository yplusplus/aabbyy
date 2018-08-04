#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100010;
vector<int> fac[N];
bool vis[N];

int gcds[555][555];


void init() {
    for (int i = 2; i < N; i++) {
        if (vis[i]) continue;
        for (int j = i; j < N; j += i) {
            vis[j] = true;
            fac[j].push_back(i);
        }
    }
    for (int i = 0; i < 555; i++)
        for (int j = 0; j < 555; j++)
            gcds[i][j] = __gcd(i, j);
}

int _gcd(int x, int y) {
    return gcds[x][y];
}

int num[N], cnt;
int c, z, m;
void factor(int n) {
    cnt = fac[c].size();
    for (int i = 0; i < fac[c].size(); i++) {
        int x = fac[c][i];
        num[i] = 0;
        while (n % x == 0) n /= x, num[i] += z;
    }
}

long long ans;
vector<int> rrr;
vector<int> rr[N];
vector<int> state;
vector<int> b[N];
int re[N];
int cc;

void dfs(int x, int pos) {
    if (pos == cnt) {
        state.push_back(0);
        for (int i = 0; i < cnt; i++) {
            rr[cc].push_back(re[i]);
            if (re[i]) state.back() |= (1 << i);
        }
        rrr.push_back(x);
        cc++;
        return;
    }
    re[pos] = 0;
    dfs(x, pos + 1);
    for (int i = 0; i < num[pos]; i++) {
        if (1LL * x * fac[c][pos] > m) break;
        x *= fac[c][pos];
        re[pos] = i + 1;
        dfs(x, pos + 1);
    }
}

long long x, y;

long long ex_gcd(long long a, long long b) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    long long d = ex_gcd(b, a % b);
    long long tmp = x;
    x = y;
    y = tmp - (a/ b) * y;
    return d;
}

void solve(long long x, long long a, long long y, long long b, long long c) {
    /*
     * 1 <= x + pa <= m
     * 1 <= y - pb <= m
     * */
    long long y2 = (y - 0)/ b;
    while (y2 * b <= y - 0) y2++;
    while (y2 * b > y - 0) y2--;
    long long y1 = (y - m) / b;
    while (y1 * b >= y - m) y1--;
    while (y1 * b < y - m) y1++;

    if (y1 > y2) return;

    long long x2 = (m - x) / a;
    while (x2 * a <= m - x) x2++;
    while (x2 * a > m - x) x2--;
    long long x1 = (0 -x) / a;
    while (x1 * a >= 0 -x) x1--;
    while (x1 * a < 0 -x) x1++;

    long long st = max(x1, y1);
    long long ed = min(x2, y2);
    if (st > ed) return;
    ans += ed - st + 1;
}

void solve(int xx, int yy, int zz) {
    int gcd = _gcd(xx, yy);
    if (zz % gcd) return;
    ex_gcd(xx, yy);
    x *= zz / gcd;
    y *= zz / gcd;
    solve(x, yy / gcd, y, xx / gcd, zz);
}

void solve(long long x, long long y, long long z, long long xx, long long yy, long long zz, long long &ansx, long long &ansy) {


    ansx = ansy = -1;
    long long t = y * xx - yy * x, tt = z * xx - zz * x;
    if (t == 0) return;
    if (tt % t) return;
    ansy = tt / t;
    if ((z - ansy * y) % x) return;
    ansx = (z - ansy * y) / x;
}


int re2[N];
bool first;
void solve(int x, int y) {
    if (x == 0 && y == 0) return;

    int nx = b[x][state[y]], ny = b[y][state[x]];
    /*
       for (int i = 0; i < cnt; i++) {
       if (rr[x][i] == 0 && rr[y][i] == 0) return;
       int d = _gcd(rr[x][i], rr[y][i]);
       if (num[i] % d) return;
       if (rr[x][i] == 0) {
       int yy = num[i] / d;
       if (yy > m) return;
       if (ny == -1) ny  = yy;
       else if (ny != yy) return;
       } else if (rr[y][i] == 0) {
       int xx = num[i] / d;
       if (xx > m) return;
       if (nx == -1) nx = xx;
       else if (nx != xx) return;
       }
       }*/

    if (x == 0) {
        for (int i = 0; i < cnt; i++)
            if (num[i] != ny * rr[y][i]) return;
        ans += m + 1;
        ans +=  (m - cc);
        return;
    }

    if (y == 0) {
        for (int i = 0; i < cnt; i++)
            if (num[i] != nx * rr[x][i]) return;
        ans += m + 1;
        ans += m - cc;
        return;
    }

    if (nx != -1 && ny != -1) {
        for (int i = 0; i < cnt; i++)
            if (nx * rr[x][i] + ny * rr[y][i] != num[i]) return;
        ans++;
        return;
    } else if (nx != -1) {
        for (int i = 0; i < cnt; i++) {
            re[i] = num[i] - nx * rr[x][i];
            if (re[i] < 0) return;
        }
        for (int i = 0; i < cnt; i++)
            if (rr[y][i] == 0) continue;
            else if (ny != -1) {
                if (ny * rr[y][i] != re[i]) return;
            } else {
                if (re[i] % rr[y][i]) return;
                ny = re[i] / rr[y][i];
                if (ny > m) return;
            }
        ans++;
    } else if (ny != -1) {
        for (int i = 0; i < cnt; i++) {
            re[i] = num[i] - ny * rr[y][i];
            if (re[i] < 0) return;
        }
        for (int i = 0; i < cnt; i++)
            if (rr[x][i] == 0) continue;
            else if (nx != -1) {
                if (nx * rr[x][i] != re[i]) return;
            } else {
                if (re[i] % rr[x][i]) return;
                nx = re[i] / rr[x][i];
                if (nx > m) return;
            }
        ans++;
    } else {
        int xx = 0, yy = 0, zz = 0;
        for (int i = 0; i < cnt; i++) {
            xx += rr[x][i];
            yy += rr[y][i];
            zz += num[i];
        }


        if (cnt == 1) {
            solve(xx, yy, zz);
        } else {
            long long ansx = -1, ansy = -1;
            bool flag = false;
            int x1 = -1, y1 = -1, z1 = -1;
            for (int i = 0; i < cnt; i++) {
                int d = _gcd(rr[x][i], rr[y][i]);
                if (i == 0) {
                    x1 = rr[x][i] / d, y1 = rr[y][i] / d, z1 = num[i] / d;
                } else {
                    int x2 = rr[x][i] / d, y2 = rr[y][i] / d, z2 = num[i] / d;
                    if (x1 == x2 && y1 == y2 && z1 == z2) continue;
                    flag = true;
                    ansx = -1, ansy = -1;
                    solve(x1, y1, z1, x2, y2, z2, ansx, ansy);
                    break;
                }
            }
            if (!flag) solve(xx, yy, zz);
            else {

                if (min(ansx, ansy) < 0 || max(ansx, ansy) > m) return;
                for (int i = 0; i < cnt; i++)
                    if (ansx * rr[x][i] + ansy * rr[y][i] != num[i]) return;
                ans++;
            }
        }
    }
}

void cal() {
    vector<int> st[1 << cnt];
    for (int i = 0; i < state.size(); i++) {
        st[state[i]].push_back(i);
    }

    for (int i = 0; i < cc; i++) {
        for (int j = 0; j < (1 << cnt); j++) {
            b[i].push_back(-1);
            if ((state[i] | j) != (1 << cnt) - 1) continue;
            if ((j & state[i]) == state[i]) continue;
            for (int k = 0; k < cnt; k++) {
                if ((state[i] & j) & (1 << k)) continue;
                if (j & (1 << k)) continue;
                if ((state[i] & (1 << k)) == 0) continue;
                if (num[k] % rr[i][k]) {
                    b[i][j] = -2;
                    break;
                }
                int p = num[k] / rr[i][k];
                if (b[i][j] == -1) b[i][j] = p;
                else if (b[i][j] != p) {
                    b[i][j] = -2;
                    break;
                }
            }
            if (b[i][j] > m) {
                b[i][j] = -2;
                continue;
            }
        }
    }

    first = true;
    int tot = 0;
    for (int i = 0; i < (1 << cnt); i++) {
        for (int j = 0; j < (1 << cnt); j++) {
            if ((i | j) != (1 << cnt) - 1) continue;
            for (int ii = 0; ii < st[i].size(); ii++) {
                int xx = st[i][ii];
                if (b[xx][j] == -2) continue;
                for (int jj = 0; jj < st[j].size(); jj++) {
                    int yy = st[j][jj];
                    if (b[yy][i] == -2) continue;
                    if (xx > yy) continue;
                    tot++;
                    long long tmp = ans;
                    ans = 0;
                    solve(xx, yy);
                    if (xx ==  yy) tmp += ans;
                    else tmp += 2 * ans;
                    ans = tmp;
                }
            }
        }
    }
    //cout << tot << " " << state.size() << endl;
}

void solve() {
    memset(re, 0, sizeof(re));
    scanf("%d%d%d", &c, &z, &m);
    if (c == 1 || z == 0) {
        long long ans = 1LL * (m  * 2) * (m * 2);
        printf("%lld\n", ans);
        return;
    }
    cc = 0;
    factor(c);
    ans = 0;
    dfs(1, 0);
    cal();
    printf("%lld\n", ans);

    state.clear();
    for (int i = 0; i < cc; i++) rr[i].clear();
    for (int i = 0; i < cc; i++)
        b[i].clear();
}

int main()
{
    init();
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; cas++) {
        printf("Case #%d: ", cas);
        solve();
    }
    return 0;
}
