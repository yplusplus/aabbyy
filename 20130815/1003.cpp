#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

const int N = 1111;
int flag[N][N];
bool visit[N][N];
int dx[] = {0, 0, -1, -1, -1, 1, 1, 1};
int dy[] = {-1, 1, -1, 0, 1, -1, 0, 1};
int n, m, k;
bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int bfs(int x, int y) {
    queue<int> que;
    que.push(x), que.push(y);
    visit[x][y] = true;
    int cnt = 0;
    while (!que.empty()) {
        x = que.front(), que.pop();
        y = que.front(), que.pop();
        if (flag[x][y] > 0) {
            cnt++;
            continue;
        }
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (check(nx, ny) && flag[nx][ny] >= 0 && !visit[nx][ny]) {
                visit[nx][ny] = true;
                que.push(nx);
                que.push(ny);
            }
        }
    }
    return cnt;
}

bool check2(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (check(nx, ny)) {
            if (flag[nx][ny] == 0) return false;
        }
    }
    return true;
}

int sg[1010 * 1010];

void getSG()
{
    memset(sg,-1,sizeof(sg));
    sg[0] = 1;
    for(int i = 1; i <= 1000 * 1000; i ++) {
        int x = 0,y = sg[i - 1];
        for(int j = 1; ; j ++)
            if(x != j && y != j) {
                sg[i] = j;
                break;
            }
    }
}

int main() {
    getSG();
    int T, Case = 1;
    cin >> T;
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        memset(flag, 0, sizeof(flag));
        int x, y;
        while (k--) {
            scanf("%d%d", &x, &y);
            flag[x][y] = -1;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (flag[i][j] == -1) continue;
                for (k = 0; k < 8; k++) {
                    x = i + dx[k], y = j + dy[k];
                    if (check(x, y) && flag[x][y] == -1) flag[i][j]++;
                }
            }
        }
        int cnt = 0;
        memset(visit, false, sizeof(visit));
        int num = 0;
        vector<int> vec;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (flag[i][j] == -1) continue;
                if (flag[i][j] > 0 && check(i, j)) num++;
                if (!visit[i][j] && flag[i][j] == 0) {
                    vec.pb(bfs(i, j));
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < vec.size(); i++) {
            ans ^= sg[vec[i]];
        }
        ans ^= (num & 1);
        printf("Case #%d: %s\n", Case++, (ans) ? "Xiemao" : "Fanglaoshi");
    }
    return 0;
}

