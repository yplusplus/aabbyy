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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int dx[] = {0, 0, -1, 1};
const int dy[] = {1, -1, 0, 0};
const int N = 20;
char maz[N][N];
int n, m, k, h;
int sx, sy, tx, ty;
bool visit[N][N];

struct Monster {
    Monster(){}
    Monster(int _bornTime) : bornTime(_bornTime) {
        hp = h;
        isPoisoned = isFrozen = false;
        pos = 0;
    }
    bool isPoisoned, isFrozen;
    int hp, pos, bornTime;
    bool operator<(const Monster &a) const {
        if (pos != a.pos) return pos > a.pos;
        return bornTime < a.bornTime;
    }
};

struct Tower {
    Tower(){}
    Tower(char _type, int _x, int _y) : type(_type), x(_x), y(_y) {}
    char type;
    int x, y;
};

bool canGo(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && (maz[x][y] == 'S' || maz[x][y] == 'T' || maz[x][y] == '.');
}

vector<pii> path;
void dfs(int x, int y) {
    visit[x][y] = true;
    path.pb(mp(x, y));
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (canGo(nx, ny) && !visit[nx][ny]) {
            dfs(nx, ny);
            return;
        }
    }
}

bool isAdjacent(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1;
}

bool isAdjacent(int x1, int y1, int pos) {
    return isAdjacent(x1, y1, path[pos].fi, path[pos].se);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k >> h;
        h = (h + 9) / 10;
        vector<Tower> tower;
        for (int i = 0; i < n; i++) {
            cin >> maz[i];
            for (int j = 0; j < m; j++) {
                if (maz[i][j] == 'X' || maz[i][j] == '.') continue;
                if (maz[i][j] == 'S') sx = i, sy = j;
                else if (maz[i][j] == 'T') tx = i, ty = j;
                else tower.pb(Tower(maz[i][j], i, j));
            }
        }
        //find s - t path
        memset(visit, false, sizeof(visit));
        path.clear();
        dfs(sx, sy);
        path.pop_back();
        //cout << path.size() << endl;
        Monster monster[55];
        int tail = 0;
        bool lost = false;
        int ans = -1;
        for (int i = 1; i <= 333; i++) {
            //poisoned && move;
            int tmpTail = 0;
            for (int j = 0; j < tail; j++) {
                if (monster[j].isPoisoned) monster[j].hp--;
                if (monster[j].hp > 0) {
                    if (monster[j].isFrozen) monster[j].isFrozen = false;
                    else if (++monster[j].pos == path.size()) {
                        lost = true;
                        break;
                    }
                    monster[tmpTail++] = monster[j];
                }
            }
            tail = tmpTail;
            if (lost) break;
            //a monster is born
            if (i <= k) {
                monster[tail++] = Monster(i);
            }
            //attact
            for (int j = 0; j < tower.size(); j++) {
                if (tower[j].type == 'F') {
                    for (int k = 0; k < tail; k++) {
                        if (isAdjacent(tower[j].x, tower[j].y, monster[k].pos)) monster[k].hp--;
                    }
                } else {
                    //find the nearest monster;
                    int idx = -1;
                    for (int k = 0; k < tail; k++) {
                        if (isAdjacent(tower[j].x, tower[j].y, monster[k].pos)) {
                            if (idx == -1 || monster[k] < monster[idx]) idx = k;
                        }
                    }
                    //cout << i << " " << idx << endl;
                    if (idx != -1) {
                        switch (tower[j].type) {
                            case 'B': monster[idx].hp--; break;
                            case 'N': monster[idx].isPoisoned = true; break;
                            case 'I': monster[idx].isFrozen = true; break;
                        }
                    }
                }
            }
            //erase hp = 0 's monster
            tmpTail = 0;
            for (int j = 0; j < tail; j++) {
                if (monster[j].hp > 0) monster[tmpTail++] = monster[j];
            }
            tail = tmpTail;
            if (i >= k && tail == 0) {
                ans = i;
                break;
            }
        }
        if (lost || tail > 0) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}
