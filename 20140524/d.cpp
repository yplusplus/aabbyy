#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 5;
const int FACE = 6;
const int M = 1 << 14;

double dp[M];
int score[FACE][FACE][FACE][FACE][FACE][14];
double prob[FACE][FACE][FACE][FACE][FACE];
double p[FACE];
int cnt[FACE];
int fac[N + 1];

int calc_upper(int target, int dice[]) {
    int res = 0;
    for (int i = 0; i < N; i++) {
        if (dice[i] == target) res += target + 1;
    }
    return res;
}

int calc_6th(int dice[]) {
    int two = 0, res = 0;
    for (int i = 0; i < FACE; i++) {
        two += cnt[i] >= 2;
        res += cnt[i] * (i + 1);
    }
    return two == 2 ? res : 0;
}

int calc_7th(int dice[]) {
    int three = 0, res = 0;
    for (int i = 0; i < FACE; i++) {
        three += cnt[i] >= 3;
        res += cnt[i] * (i + 1);
    }
    return three ? res : 0;
}

int calc_8th(int dice[]) {
    int four = 0, res = 0;
    for (int i = 0; i < FACE; i++) {
        four += cnt[i] >= 4;
        res += cnt[i] * (i + 1);
    }
    return four ? res : 0;
}

int calc_9th(int dice[]) {
    int three = 0, two = 0;
    for (int i = 0; i < FACE; i++) {
        two += cnt[i] == 2;
        three += cnt[i] == 3;
    }
    return three && two ? 25 : 0;
}

int calc_10th(int dice[]) {
    int sum[10] = {0};
    for (int i = 5; i >= 0; i--) {
        sum[i] = sum[i + 1] + (cnt[i] >= 1);
    }
    for (int i = 2; i >= 0; i--) {
        if (sum[i] - sum[i + 4] == 4) return 30;
    }
    return 0;
}

int calc_11th(int dice[]) {
    int sum[10] = {0};
    for (int i = 5; i >= 0; i--) {
        sum[i] = sum[i + 1] + (cnt[i] >= 1);
    }
    for (int i = 1; i >= 0; i--) {
        if (sum[i] - sum[i + 5] == 5) return 40;
    }
    return 0;

}

int calc_12th(int dice[]) {
    return dice[0] == dice[4] ? 50 : 0;
}

int calc_13th(int dice[]) {
    int res = 0;
    for (int i = 0; i < FACE; i++) {
        res += cnt[i] * (i + 1);
    }
    return res;
}

void solve() {
    for (int a = 0; a < FACE; a++) {
        for (int b = a; b < FACE; b++) {
            for (int c = b; c < FACE; c++) {
                for (int d = c; d < FACE; d++) {
                    for (int e = d; e < FACE; e++) {
                        int dice[N] = {a, b, c, d, e};
                        double t = 1;
                        memset(cnt, 0, sizeof(cnt));
                        for (int i = 0; i < N; i++) {
                            t *= p[dice[i]];
                            cnt[dice[i]]++;
                        }
                        t *= fac[5];
                        for (int i = 0; i < FACE; i++) { t /= fac[cnt[i]]; }
                        prob[a][b][c][d][e] = t;
                        for (int i = 0; i < FACE; i++) { score[a][b][c][d][e][i] = calc_upper(i, dice); }
                        score[a][b][c][d][e][6] = calc_6th(dice);
                        score[a][b][c][d][e][7] = calc_7th(dice);
                        score[a][b][c][d][e][8] = calc_8th(dice);
                        score[a][b][c][d][e][9] = calc_9th(dice);
                        score[a][b][c][d][e][10] = calc_10th(dice);
                        score[a][b][c][d][e][11] = calc_11th(dice);
                        score[a][b][c][d][e][12] = calc_12th(dice);
                        score[a][b][c][d][e][13] = calc_13th(dice);
                    }
                }
            }
        }
    }
    memset(dp, 0, sizeof(dp));
    for (int mask = 1; mask < M; mask++) {
        for (int a = 0; a < FACE; a++) {
            for (int b = a; b < FACE; b++) {
                for (int c = b; c < FACE; c++) {
                    for (int d = c; d < FACE; d++) {
                        for (int e = d; e < FACE; e++) {
                            double t = 0;
                            for (int i = 0; i < 14; i++) {
                                if (mask >> i & 1) {
                                    t = max(t, (score[a][b][c][d][e][i] + dp[mask ^ (1 << i)]) * prob[a][b][c][d][e]);
                                }
                            }
                            dp[mask] += t;
                        }
                    }
                }
            }
        }
    }
    printf("%.6f\n", dp[M - 1]);
}

int main() {
    fac[0] = 1; for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < FACE; i++) scanf("%lf", &p[i]);
        printf("Case #%d: ", Case++);
        solve();
    }
    return 0;
}
