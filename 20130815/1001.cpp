#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

const int N = 20010;
struct point
{
    int x,y,z,id;
    void read() {
        scanf("%d%d",&x,&y);
        z = (int)sqrt(y * 1.0);
    }
    friend bool operator < (const point &p,const point &q) {
        if(p.z != q.z) return p.z < q.z;
        return p.x < q.x;
    }
}a[N];

int phi[N],com[N];
vector<int> v[N];

int get_phi(int n)
{
    int ans = n;
    for(int i = 2; i * i <= n; i ++) {
        if(n % i) continue;
        while(n % i == 0) n /= i;
        ans = ans / i * (i - 1);
    }
    if(n > 1) ans = ans / n * (n - 1);
    return ans;
}
    
void init()
{
    phi[0] = 0;
    com[0] = 0;
    for(int i = 1; i < N;i ++) {
        for(int j = 1; j * j <= i; j ++) {
            if(i % j) continue;
            v[i].push_back(j);
            if(j * j != i) v[i].push_back(i / j);
        }
        phi[i] = get_phi(i);
        com[i] = i * (i - 1) / 2;
    }
}

long long ans[N];
int visit[N];

int cal(int x)
{
    return com[visit[x]] * phi[x];
}

int main()
{
    int cas = 0;
    init();
    int t,n,m,c[N];
    scanf("%d",&t);
    while(t --) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i ++) scanf("%d",&c[i]);
        scanf("%d",&m);
        for(int i = 1; i <= m; i ++) {
            a[i].read();
            a[i].id = i;
        }
        sort(a + 1,a + m + 1);
        int i = 1;
        while(i <= m) {
            int j = i;
            while(j <= m && a[j].z == a[i].z) j ++;
            memset(visit,0,sizeof(visit));
            long long sum = 0;
            for(int k = i; k < j; k ++) {
                if(k == i) {
                    for(int r = a[k].x; r <= a[k].y; r ++) {
                        int x = c[r];
                        for(int p = 0; p < v[x].size(); p ++) {
                            sum -= cal(v[x][p]);
                            visit[v[x][p]] ++;
                            sum += cal(v[x][p]);
                        }
                    }
                    ans[a[k].id] = sum;
                }
                else {
                    for(int r = a[k - 1].x; r < a[k].x; r ++) {
                        int x = c[r];
                        for(int p = 0; p < v[x].size(); p ++) {
                            sum -= cal(v[x][p]);
                            visit[v[x][p]] --;
                            sum += cal(v[x][p]);
                        }
                    }
                    if(a[k - 1].y < a[k].y) {
                        for(int r = a[k - 1].y + 1; r <= a[k].y; r ++) {
                            int x = c[r];
                            for(int p = 0; p < v[x].size(); p ++) {
                                sum -= cal(v[x][p]);
                                visit[v[x][p]] ++;
                                sum += cal(v[x][p]);
                            }
                        }
                    }       
                    else {
                        for(int r = a[k].y + 1; r <= a[k - 1].y; r ++) {
                            int x = c[r];
                            for(int p = 0; p < v[x].size(); p ++) {
                                sum -= cal(v[x][p]);
                                visit[v[x][p]] --;
                                sum += cal(v[x][p]);
                            }
                        }
                    }
                    ans[a[k].id] = sum;
                }                       
            }
            i = j;
        }
        printf("Case #%d:\n",++ cas);
        for(int i = 1; i <= m; i ++)
            printf("%I64d\n",ans[i]);
    }
    return 0;
}



