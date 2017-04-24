#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 210;
struct point
{
    double x,y;
    void read() {
        scanf("%lf%lf",&x,&y);
    }
}a[N],og;

struct node
{
    double dist;
    int id;
    node() {}
    node(int id,double dist):id(id),dist(dist) {}
}c[N][N],b[N][N];
    
int num[N],f[N];
double dist(point p,point q)
{
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

void update(double &min,double &tdis,int &id1,int &id2,int &id3,int &id4,double mx,int i,int j,int k,int r)
{
    if(min > mx) {
        min = mx;
        id1 = i;
        id2 = j;
        id3 = k;
        id4 = r;
        tdis = dist(og,a[id1]) + dist(og,a[id2]) + dist(og,a[id3]) + dist(og,a[id4]);
        return;
    }
    if(fabs(min - mx) < 1e-8) {
        double tmp = dist(og,a[i]) + dist(og,a[j]) + dist(og,a[k]) + dist(og,a[r]);
        if(tmp < tdis) {
            tdis = tmp;
            min = mx;
            id1 = i;
            id2 = j;
            id3 = k;
            id4 = r;
        }
    }
}

int visit[N];
void find(int n,int &mid1,int &mid2,int &mid3,double &min1,double &min2,double &min3,node a[],int m)
{
    for(int i = 1; i <= m; i ++) {
        if(visit[a[i].id]) continue;
        if(a[i].dist < min1) {
            min3 = min2;
            mid3 = mid2;
            min2 = min1;
            mid2 = mid1;
            min1 = a[i].dist;
            mid1 = a[i].id;
        }
        else if(a[i].dist < min2) {
            min3 = min2;
            mid3 = mid2;
            min2 = a[i].dist;
            mid2 = a[i].id;
        }
        else if(a[i].dist < min3) {
            min3 = a[i].dist;
            mid3 = a[i].id;
        }
    }
}
            
        
void solve()
{
    int n,m;
    og.read();
    scanf("%d",&n);
    m = n * 4;
    memset(num,0,sizeof(num));
    memset(f,0,sizeof(f));
    for(int i = 1; i <= m; i ++) a[i].read();
    for(int i = 1; i <= m; i ++) {
        for(int j = 1; j <= m; j ++) {
            if(i == j) continue;
            c[i][++ num[i]] = node(j,dist(og,a[j]) + dist(a[j],a[i]));
        }
        for(int j = 1; j <= m; j ++) {
            if(i == j) continue;
            b[i][++ f[i]] = node(j,dist(a[j],a[i]));
        }   
    }
    memset(visit,0,sizeof(visit));
    double ans = 0;
    int midx1[N],midx2[N],midx3[N];
    double minx1[N],minx2[N],minx3[N];
    int mmidx1[N],mmidx2[N],mmidx3[N];
    double mminx1[N],mminx2[N],mminx3[N];
    while(n --) {
        double min = 1e20,tdis = 1e20;
        int id1,id2,id3,id4;
        for(int i = 0; i <= m; i ++) {
            midx1[i] = midx2[i] = midx3[i] = mmidx1[i] = mmidx2[i] = mmidx3[i] = -1;
            minx1[i] = minx2[i] = minx3[i] = mminx1[i] = mminx2[i] = mminx3[i] = 1e20;
        }
        
        for(int i = 1; i <= m; i ++) {
            if(visit[i]) continue;
            find(m,midx1[i],midx2[i],midx3[i],minx1[i],minx2[i],minx3[i],c[i],num[i]);
            find(m,mmidx1[i],mmidx2[i],mmidx3[i],mminx1[i],mminx2[i],mminx3[i],b[i],f[i]);
        }
        for(int i = 1; i <= m; i ++) {
            if(visit[i]) continue;
            for(int j = 1; j <= m; j ++) {
                if(i == j || visit[j]) continue;
                int mid1,mid2;
                double min1,min2;
                if(midx1[i] == j) {
                    mid1 = midx2[i];
                    min1 = minx2[i];
                    mid2 = midx3[i];
                    min2 = minx3[i];
                }
                else if(midx2[i] == j) {
                    mid1 = midx1[i];
                    min1 = minx1[i];
                    mid2 = midx3[i];
                    min2 = minx3[i];
                }
                else {
                    mid1 = midx1[i];
                    min1 = minx1[i];                    
                    mid2 = midx2[i];
                    min2 = minx2[i];        
                }            
                
                int mmid1,mmid2;
                double mmin1,mmin2;
                if(mmidx1[j] == i) {
                    mmid1 = mmidx2[j];
                    mmin1 = mminx2[j];
                    mmid2 = mmidx3[j];
                    mmin2 = mminx3[j];
                }
                else if(mmidx2[j] == i) {
                    mmid1 = mmidx1[j];
                    mmin1 = mminx1[j];
                    mmid2 = mmidx3[j];
                    mmin2 = mminx3[j];
                }
                else {
                    mmid1 = mmidx1[j];
                    mmin1 = mminx1[j];             
                    mmid2 = mmidx2[j];
                    mmin2 = mminx2[j];      
                } 
                
                double dis = dist(a[i],a[j]);
                if(mid1 == mmid1) {
                    update(min,tdis,id1,id2,id3,id4,dis + min1 + mmin2,mid1,mmid2,i,j);
                    update(min,tdis,id1,id2,id3,id4,dis + min2 + mmin1,mid2,mmid1,i,j);
                }
                else update(min,tdis,id1,id2,id3,id4,dis + min1 + mmin1,mid1,mmid1,i,j);
            }
        }
                
        /*
        for(int i = 1; i <= m; i ++) {
            if(visit[i]) continue;
            int mid1 = -1,mid2 = -1;
            double min1 = 1e20,min2 = 1e20;
            find(m,mid1,mid2,min1,min2,c[i],num[i]);
            for(int j = 1; j <= m; j ++) {
                if(visit[j] || i == j) continue;
                double dis = dist(a[i],a[j]);
                visit[j] = 1;
            
                int mmid1 = -1,mmid2 = -1;
                double mmin1 = 1e20,mmin2 = 1e20;
                find(m,mmid1,mmid2,mmin1,mmin2,b[j],f[j]);*/
        /*
                visit[j] = 0;
            }
            visit[i] = 0;
        }*/
        visit[id1] = visit[id2] = visit[id3] = visit[id4] = 1;
        //cout << id1 << " " << id2 << " " << id3 << " " << id4 << " " << min << endl;
        ans += min;
    }
    printf("%.2lf\n",ans);
}
    
int main()
{
    int t;
    scanf("%d",&t);
    for(int cas = 1; cas <= t; cas ++) {
        printf("Case #%d: ",cas);
        solve();
    }
    return 0;
}
    

