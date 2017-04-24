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
#define ll long long
#define ull unsigned long long
typedef unsigned int uint;
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

int row[10];
set<uint> state[10];
int add[10];
int sub[10];
bool cant[10];
void dfs(int id, int mask, int i) {
    if (i == 8) {
        for (set<uint>::iterator it = state[id - 1].begin(); it != state[id - 1].end(); it++) {
            bool found = false;
            int cnt[8] = {0};
            uint t = *it;
            for (int j = 0; j < 8; j++) {
                cnt[j] = t & 15;
                t >>= 4;
                cnt[j] -= sub[j];
                if (cnt[j] < 0) found = true;
            }
            if (found) continue;
            t = 0;
            for (int j = 7; j >= 0; j--) {
                cnt[j] += add[j];
                if (cant[j]) cnt[j] = 0;
                t <<= 4;
                t += cnt[j];
            }
            state[id].insert(t);
        }
        return;
    }
    if (~mask >> i & 1) dfs(id, mask, i + 1);
    else {
        //left
        if (i - 1 >= 0) {
            sub[i - 1] += 1;
            add[i] += 1;
            dfs(id, mask, i + 1);
            add[i] -= 1;
            sub[i - 1] -= 1;
        }
        //not eat
        cant[i] = true;
        dfs(id, mask, i + 1);
        cant[i] = false;
        //right
        if (i + 1 < 8) {
            sub[i + 1] += 1;
            add[i] += 1;
            dfs(id, mask, i + 1);
            add[i] -= 1;
            sub[i + 1] -= 1;
        }
    }
}

int main() {
    int n;
    while (~scanf("%d", &n)) {
        memset(row, 0, sizeof(row));
        for (int i = 0; i < n; i++) {
            char pos[5];
            scanf("%s", pos);
            row[pos[1] - '1'] |= (1 << (pos[0] - 'a'));
        }
        uint mask = 0;
        for (int i = 0; i < 8; i++) {
            state[i].clear();
            mask <<= 4;
            mask |= 1;
        }
        state[0].insert(mask);
        for (int i = 1; i < 8; i++) {
            memset(cant, false, sizeof(cant));
            memset(add, 0, sizeof(add));
            memset(sub, 0, sizeof(sub));
            dfs(i, row[i], 0);
        }
        int ans = 0;
        for (set<uint>::iterator it = state[7].begin(); it != state[7].end(); it++) {
            uint t = *it;
            int cnt = 0;
            for (int i = 0; i < 8; i++) {
                if (t & 15) cnt++;
                t >>= 4;
            }
            ans = max(ans, cnt);
        }
        cout << ans << endl;
    }
    return 0;
}
