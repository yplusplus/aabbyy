#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

const int M = 55555;
const int N = 22;

short dist[1 << 6][N][M << 1];
char board[N][N];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int sx, sy, tx, ty;
int id[N][N];
int tot, n, m;
int touchFace[4] = {0, 2, 4, 5};
int change[4][6] = {
    {3, 0, 1, 2, 4, 5},
    {1, 2, 3, 0, 4, 5},
    {0, 4, 2, 5, 3, 1},
    {0, 5, 2, 4, 1, 3}
};
map<int, int> hashMap;
int record[M << 1];
pair<int, int> grid[N];

bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && board[x][y] != '#';
}

int vec2int(vector<int> &pos) {
    int res = 0;
    int pw = 1;
    for (int i = 0; i < pos.size(); i++) {
        res += pw * pos[i];
        pw *= tot + 1;
    }
    return res;
}

void int2vec(int value, vector<int> &pos) {
    pos.resize(6);
    for (int i = 0; i < 6; i++) {
        pos[i] = (value % (tot + 1));
        value /= (tot + 1);
    }
}

int find(const vector<int> &pos, int u) {
    for (int i = 0; i < pos.size(); i++) {
        if (pos[i] == u) return i;
    }
    return -1;
}

int hashBoard(int x) {
    if (hashMap.count(x)) return hashMap[x];
    hashMap[x] = hashMap.size();
    record[hashMap[x]] = x;
    return hashMap[x];
}

void changeState(int &mask, int x, int y, int nx, int ny, int runId, vector<int> &pos) {
    int face = touchFace[runId];
    int ret = find(pos, id[nx][ny]);
    if ((mask >> face & 1) && ret == -1) {
        mask ^= (1 << face);
        for (int i = 0; i < pos.size(); i++) {
            if (pos[i] == 0) {
                pos[i] = id[nx][ny];
                break;
            }
        }
        sort(pos.begin(), pos.end());
    } else if ((~mask >> face & 1) && ret != -1) {
        mask ^= (1 << face);
        pos[ret] = 0;
        sort(pos.begin(), pos.end());
    }
    int nmask = 0;
    for (int i = 0; i < 6; i++) {
        nmask |= (mask >> change[runId][i] & 1) << i;
    }
    mask = nmask;
}

void solve() {
    vector<int> pos, npos;
    tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] != '#') {
                id[i][j] = ++tot;
                grid[tot] = make_pair(i, j);
            }
            if (board[i][j] == 'C') sx = i, sy = j;
            if (board[i][j] == 'G') tx = i, ty = j;
            if (board[i][j] == 'P') pos.push_back(id[i][j]);
        }
    }
    //cout << n << " x " << m << " " << tot << endl;
    memset(dist, -1, sizeof(dist));
    hashMap.clear();
    int mask, u, posValue, v;
    queue<int> que;
    sort(pos.begin(), pos.end());
    posValue = vec2int(pos);
    v = hashBoard(posValue);
    que.push(0);
    que.push(id[sx][sy]);
    que.push(v);
    dist[0][id[sx][sy]][v] = 0;
    while (!que.empty()) {
        mask = que.front(); que.pop();
        u = que.front(); que.pop();
        v = que.front(); que.pop();
        posValue = record[v];
        int2vec(posValue, pos);
        int x = grid[u].first, y = grid[u].second;
        /*
           cout << "**********" << endl;
           cout << mask << " " << x << " " << y << endl;
           for (int i = 0; i < 6; i++) { cout << pos[i] << " "; } cout << endl;
         */
        //getchar(); getchar();
        if (mask == (1 << 6) - 1 && x == tx && y == ty) {
            printf("%d\n", dist[(1 << 6) - 1][u][v]);
            return;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (!check(nx, ny)) continue;
            vector<int> npos(pos);
            int nmask = mask;
            changeState(nmask, x, y, nx, ny, i, npos);
            //for (int i = 0; i < 6; i++) { cout << npos[i] << " "; } cout << endl;
            int nposValue = vec2int(npos);
            int ret = hashBoard(nposValue);
            if (dist[nmask][id[nx][ny]][ret] == -1) {
                dist[nmask][id[nx][ny]][ret] = dist[mask][u][v] + 1;
                que.push(nmask);
                que.push(id[nx][ny]);
                que.push(ret);
            }
        }
    }
    //cout << hashMap.size() << endl;
    puts("-1");
}

int main() {
    while (gets(board[0])) {
        n = 1;
        char *str;
        while ((str = gets(board[n])) && strlen(board[n]) > 0) { n++; }
        m = strlen(board[0]);
        solve();
        if (str == NULL) break;
    }
    return 0;
}
