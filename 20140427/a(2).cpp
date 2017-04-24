// by mgq
#include <bits/stdc++.h>
using namespace std;

const int oo = 2147483647;
const int N = 1010;
int slack[N],usedx[N],usedy[N],match[N],w[N][N];
int n,m;
int lx[N],ly[N];
int dfs(int u)
{
	usedx[u] = 1;
	for(int i = 1; i <= m; i ++)
		if(!usedy[i]) {
			int temp = lx[u] + ly[i] - w[u][i];
			if(temp) {
				if(slack[i] > temp) slack[i] = temp;
			}
			else {
				usedy[i] = 1;
				if(match[i] == -1 || dfs(match[i])) {
					match[i] = u;
					return 1;
				}
			}
		}
	return 0;
}

void km()
{
	memset(match,-1,sizeof(match));
	for(int i = 1; i <= n; i ++) {
		lx[i] = -oo;
		for(int j = 1; j <= m; j ++)
			lx[i] = max(lx[i],w[i][j]);
	}
	memset(ly,0,sizeof(ly));
	for(int x = 1; x <= n; x ++) {
		fill(slack,slack + N,oo);
		while(1) {
			memset(usedx,0,sizeof(usedx));
			memset(usedy,0,sizeof(usedy));
			if(dfs(x)) break;
			int minf = oo;
			for(int j = 1; j <= m; j ++) {
				if(!usedy[j] && minf > slack[j])
					minf = slack[j];
			}
			for(int i = 1; i <= n; i ++)
				if(usedx[i]) lx[i] -= minf;
			for(int i = 1; i <= m;i ++)
				if(usedy[i]) ly[i] += minf;
				else slack[i] -= minf;
		}
	}
}

int grid[255][255];
int Map[255][255];
int matchx[255];
int revx[255],revy[255];
bool visit[255][255];
int rev2x[N],rev2y[N];

int main()
{
    freopen("agrarian.in","r",stdin);
    freopen("agrarian.out","w",stdout);
    int h,wt,s,x,y;
    scanf("%d%d%d%d",&h,&wt,&n,&s);
    for(int i = 1; i <= n; i ++) {
        scanf("%d%d",&x,&y);
        assert(0 == grid[x][y]);
        grid[x][y] = i;
        revx[i] = x;
        revy[i] = y;
    }
    while(s --) {
        scanf("%d%d",&x,&y);
        assert(x >= 1 && x <= h && y >= 1 && y <= wt);
        grid[x][y] = -1;
    }
    for(int i = 1; i <= h; i ++)
        for(int j = 1; j <= wt; j ++)
            if(!grid[i][j]) {
                Map[i][j] = ++ m;
                rev2x[m] = i;
                rev2y[m] = j;
            }
    for(int i = 1; i <= h; i ++)
        for(int j = 1; j <= wt; j ++)
            if(grid[i][j] > 0)
                for(int k = 1; k <= h; k ++)
                    for(int r = 1; r <= wt; r ++)
                        if(Map[k][r] > 0)
                            w[grid[i][j]][Map[k][r]] = 1000 -(abs(i - k) + abs(j - r));
    km();
    memset(visit,false,sizeof(visit));
    int cost = 0;
    int cc = 0;
    for(int i = 1; i <= m; i ++)
        if(match[i] != -1) cc ++,cost += w[match[i]][i],matchx[match[i]] = i;
    assert(cc == n);
    for(int i = 1; i <= n; i ++)
        if(!matchx[i]) assert(1 == 2);
    for(int i = 1; i <= h; i ++)
        for(int j = 1; j <= wt; j ++)
            if(Map[i][j] > 0 && match[Map[i][j]] != -1) visit[i][j] = true;
    while(1) {
        bool change = false;
        for(int i = 1; i <= n; i ++) {
            bool flag = false;
            for(int j = 1; j <= h && !flag; j ++) {
                for(int k = 1; k <= wt && !flag; k ++) {
                    if(grid[j][k]) continue;
                    if(w[i][Map[j][k]] == w[i][matchx[i]]) {
                        x = rev2x[matchx[i]];
                        y = rev2y[matchx[i]];
                        if(visit[j][k]) continue;
                        if(x == j && y == k) continue;
                        if(x < j || (x == j && y < k)) continue;
                        visit[x][y] = false;
                        visit[j][k] = true;
                        matchx[i] = Map[j][k];
                        change = flag = true;
                    }
                }
            }
        }
        if(!change) break;
    }
    int tmp = 0;
    for(int i = 1; i <= n; i ++)
        tmp += w[i][matchx[i]];
    assert(tmp == cost);
    vector<int> v[255];
    stack<int> stk;
    int ind[255];
    memset(ind,0,sizeof(ind));
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= n; j ++) {
            if(i == j) continue;
            x = rev2x[matchx[i]];
            y = rev2y[matchx[i]];
            int tx = rev2x[matchx[j]];
            int ty = rev2y[matchx[j]];
            if(w[j][matchx[j]] < w[j][matchx[i]] ||
               ((x < tx || (x == tx && y < ty)) && w[j][matchx[j]] == w[j][matchx[i]])) {
                   v[i].push_back(j);
                   ind[j] ++;
               }
        }
    }
    int tot = 0;
    for(int i = 1; i <= n; i ++)
        if(!ind[i]) stk.push(i);
    int sq[255];
    while(!stk.empty()) {
        tot ++;
        int u = stk.top();
        sq[tot] = u;
        stk.pop();
        printf("%d ",u);
        for(int i = 0; i < v[u].size(); i ++) {
            x = v[u][i];
            ind[x] --;
            if(!ind[x]) stk.push(x);
        }
    }
    assert(tot == n);
    printf("\n");
    int sum = 0;
    memset(visit,0,sizeof(visit));
    for(int i = 1; i <= tot; i ++) {
        int u = sq[i];
        int minx = oo;
        for(int j = 1; j <= h; j ++)
            for(int k = 1; k <= wt; k ++)
                if(!visit[j][k] && Map[j][k] > 0) minx = min(minx,w[u][Map[j][k]]);
        bool flag = false;
        for(int j = 1; j <= h && !flag; j ++)
            for(int k = 1; k <= wt && !flag; k ++)
                if(Map[j][k] > 0 && !visit[j][k] && minx == w[u][Map[j][k]]) {
                    flag = true;
                    visit[j][k] = true;
                }
        sum += minx;
        //cout << u << " " << minx << endl;
    }
    assert(sum <= cost);
    //cout << cost << " " << sum << endl;
    return 0;
}