#include <bits/stdc++.h>
using namespace std;

struct point
{
    int x,y,z;
    friend bool operator < (const point &p,const point &q) {
        return p.x > q.x;
    }
    void read() {
        scanf("%d%d%d",&x,&y,&z);
    }
}a[1010];

int main()
{
    int n;
    int visit[1010];
    while(scanf("%d",&n) != EOF) {
        int ans = 0;
        memset(visit,0,sizeof(visit));
        for(int i = 0; i < n; i ++) {
            a[i].read();
            ans += a[i].y * a[i].z;
        }
        sort(a,a + n);
        for(int i = 0; i < n; i ++) {
            int mx = -0x7fffffff,id = -1;
            for(int j = 0; j < n; j ++) {
                if(visit[j]) continue;
                if(mx < a[j].z * a[i].x && a[i].x < a[j].y) {
                    mx = a[j].z * a[i].x;
                    id = j;
                }
            }
            if(id != -1) {
                ans -= mx;
                visit[id] = 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

