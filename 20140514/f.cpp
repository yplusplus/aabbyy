#include <bits/stdc++.h>
using namespace std;

const int N = 444;
const double eps = 1e-8;
int n, m;
double dp[N][N][2];
int dist2[N][N];
double dist[N][N];

struct Node {
    int v;
    pair<int, int> a;
    Node(int v, pair<int, int> a) : v(v), a(a) {}
    bool operator <(const Node &x) const { return a < x.a; }
    void output() { cout << v << " " << a.first << " " << a.second << endl; }
};

vector<Node> vec[N][2];

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    void read() { scanf("%d%d", &x, &y); }
} point[N];

/*
struct Line {
    Point s, t;
    Line() {}
    Line(Point s, Point t) : s(s), t(t) {}
    Point vec() const { return Point(t.x - s.x, t.y - s.y); }
} ;
inline int cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
inline bool isParallel(const Line &a, const Line &b) { return cross(a.vec(), b.vec()) == 0; }
*/

void addedge(int a, int b) {
    //0
    if (point[a].x != point[b].x) {
        if (point[a].x > point[b].x) swap(a, b);
        vec[b][0].push_back(Node(a, pair<int, int>(point[a].x - point[b].x, point[a].y - point[b].y)));
    }
    //1
    if (point[a].y != point[b].y) {
        if (point[a].y > point[b].y) swap(a, b);
        vec[b][1].push_back(Node(a, pair<int, int>(point[a].x - point[b].x, point[a].y - point[b].y)));
    }
}

int sq(int x) { return x * x; }
int get_dist2(int a, int b) { return sq(point[a].x - point[b].x) + sq(point[a].y - point[b].y); }

bool visit[N][N][2];
pair<int, int> pre[N][N][2];
//0 - x, 1 - y
double dfs(int a, int b, int c) {
    assert(a != b);
    if (visit[a][b][c]) return dp[a][b][c];
    if (visit[b][a][c]) {
        dp[a][b][c] = dp[b][a][c];
        pre[a][b][c] = pre[b][a][c];
        swap(pre[a][b][c].first, pre[a][b][c].second);
        return dp[a][b][c];
    }
    visit[a][b][c] = true;
    double &res = dp[a][b][c];
    res = 0;
    int j = 0;
    for (int i = 0; i < vec[a][c].size() && j < vec[b][c].size(); i++) {
        while (j < vec[b][c].size() && (vec[b][c][j].a < vec[a][c][i].a)) j++;
        if (j < vec[b][c].size() && vec[b][c][j].a == vec[a][c][i].a) {
            int na = vec[a][c][i].v, nb = vec[b][c][j].v;
            double tmp = dist[na][a] + dfs(na, nb, c);
            if (tmp > res) {
                res = tmp;
                pre[a][b][c] = pair<int, int>(na, nb);
            }
        }
    }
    return res;
}

vector<int> path[2];

void get_path(int a, int b, int c) {
    if (a == -1) return;
    path[0].push_back(a);
    path[1].push_back(b);
    get_path(pre[a][b][c].first, pre[a][b][c].second, c);
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist2[i][j] = get_dist2(i, j);
            dist[i][j] = sqrt((double)dist2[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            sort(vec[i][j].begin(), vec[i][j].end());
        }
    }
    memset(visit, 0, sizeof(visit));
    memset(pre, -1, sizeof(pre));
    double ans = 0.0;
    int t1 = -1, t2 = -1, t3 = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = 0; k < 2; k++) {
                double ret = dfs(i, j, k);
                if (ans < ret) {
                    ans = ret;
                    t1 = i, t2 = j, t3 = k;
                }
            }
        }
    }
    memset(pre,-1,sizeof(pre));
    memset(visit,0,sizeof(visit));
    memset(dp,0,sizeof(dp));
    if(t1 != -1) dfs(t1,t2,t3);
    printf("%.20f\n", ans);
    //assert(t1 != -1);
    if (t1 != -1) {
        get_path(t1, t2, t3);
        int sz = path[0].size();
        if (sz <= 1) return;
        printf("%d\n", sz);
        for (int j = 0; j < 2; j++) {
            reverse(path[j].begin(), path[j].end());
            for (int i = 0; i < sz; i++) {
                printf("%d%c", path[j][i], i == sz - 1 ? '\n' : ' ');
            }
        }
    }
}

int main() {
    freopen("london.in", "r", stdin);
    freopen("london.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) point[i].read();
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            vec[i][j].clear();
        }
    }
    */
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        addedge(a, b);
    }
    solve();
    return 0;
}
