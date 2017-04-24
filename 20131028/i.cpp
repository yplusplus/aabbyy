#include <bits/stdc++.h>
using namespace std;

struct point
{
    int id,val;
    point() {}
    point(int id,int val):id(id),val(val) {}
    friend bool operator < (const point &p,const point &q) {
        return p.val < q.val;
    }
};

vector<point> v[4];
int sum[4][5010];

int main()
{
    memset(sum,0,sizeof(sum));
    int n,a,b;
    cin >> n >> a >> b;
    int x,y;
    for(int i = 1; i <= n; i ++) {
        scanf("%d%d",&x,&y);
        v[x].push_back(point(i,y));
    }
    for(int i = 1; i <= 3; i ++)
        sort(v[i].begin(),v[i].end());
    for(int i = 1; i <= 3; i ++) {
        for(int j = 0; j < v[i].size(); j ++) {
            if(j == 0) sum[i][j] = v[i][j].val;
            else sum[i][j] = sum[i][j - 1] + v[i][j].val;
        }
    }
    int maxn = 0;
    int cost = 0;
    int z;
    x = y = z = 0;
    for(int i = 0; i <= a && i <= v[1].size(); i ++)
        for(int j = 0; j <= b && j <= v[2].size(); j ++) {
            int xx = i;
            int yy = j;
            int zz = min(a + b - xx - yy,(int)v[3].size());
            int tmp = 0;
            if(i) tmp += sum[1][i - 1];
            if(j) tmp += sum[2][j - 1];
            if(zz) tmp += sum[3][zz - 1];
            if(xx + yy + zz > maxn) {
                maxn = xx + yy + zz;
                x = xx;
                y = yy;
                z = zz;
                cost = tmp;
            }
            else if(xx + yy + zz == maxn && cost > tmp) {
                cost = tmp;
                x = xx;
                y = yy;
                z = zz;
            }
            //cout << "fuck " << xx + yy + zz << " " << maxn << endl;
        }
    printf("%d %d\n",maxn,cost);
    for(int i = 0; i < x; i ++)
        printf("%d %d\n",v[1][i].id,i + 1);
    for(int i = 0; i < z; i ++)
        printf("%d %d\n",v[3][i].id,x + i + 1);
    for(int i = 0; i < y; i ++)
        printf("%d %d\n",v[2][i].id,i + max(a,x + z) + 1);
    return 0;
}

