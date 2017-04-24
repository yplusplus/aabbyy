#include <bits/stdc++.h>
using namespace std;

const int oo = -0x7fffffff;
struct point
{
    int x1,y1,z1,x2,y2,z2;
    point() {}
    point(int x1,int y1,int z1,int x2,int y2,int z2):x1(x1),y1(y1),z1(z1),x2(x2),y2(y2),z2(z2) {}
};
vector<point> v[3];

bool check_xy(vector<point> vx,vector<point> vy)
{
    if(!vx.size() || !vy.size()) return true;
    int rad = vx[0].y2 - vx[0].y1;
    int lx = oo,rx = -oo,ly = oo,ry = -oo,lz = oo,rz = -oo;
    for(int i = 0; i < vx.size(); i ++) {
        lx = max(lx,vx[i].x1 - rad);
        rx = min(rx,vx[i].x2);
        ly = max(ly,vx[i].y1);
        ry = min(ry,vx[i].y2);
        lz = max(lz,vx[i].z1 - rad);
        rz = min(rz,vx[i].z2);
    }
    for(int i = 0; i < vy.size(); i ++) {
        if(!(vy[i].x1 > lx && vy[i].x1 < rx)) return false;
        if(!(vy[i].y1 > ly && vy[i].y1 < ry)) return false;
        if(!(vy[i].z1 > lz && vy[i].z1 < rz)) return false;
    }

    return true;
}

bool check_xz(vector<point> vx,vector<point> vy)
{
    if(!vx.size() || !vy.size()) return true;
    int rad = vx[0].y2 - vx[0].y1;
    int lx = oo,rx = -oo,ly = oo,ry = -oo,lz = oo,rz = -oo;
    for(int i = 0; i < vx.size(); i ++) {
        lx = max(lx,vx[i].x1 - rad);
        rx = min(rx,vx[i].x2);
        ly = max(ly,vx[i].y1 - rad);
        ry = min(ry,vx[i].y2);
        lz = max(lz,vx[i].z1);
        rz = min(rz,vx[i].z2);
    } 
    for(int i = 0; i < vy.size(); i ++) {
        if(!(vy[i].x1 > lx && vy[i].x1 < rx)) return false;
        if(!(vy[i].y1 > ly && vy[i].y1 < ry)) return false;
        if(!(vy[i].z1 > lz && vy[i].z1 < rz)) return false;
    }
    return true;
}

bool check_yz(vector<point> vx,vector<point> vy)
{
    if(!vx.size() || !vy.size()) return true;
    int rad = vy[0].y2 - vy[0].y1;
    int lx = oo,rx = -oo,ly = oo,ry = -oo,lz = oo,rz = -oo;
    for(int i = 0; i < vx.size(); i ++) {
        lx = max(lx,vx[i].x1 - rad);
        rx = min(rx,vx[i].x2);
        ly = max(ly,vx[i].y1 - rad);
        ry = min(ry,vx[i].y2);
        lz = max(lz,vx[i].z1);
        rz = min(rz,vx[i].z2);
    }
    for(int i = 0; i < vy.size(); i ++) {
        if(!(vy[i].x1 > lx && vy[i].x1 < rx)) return false;
        if(!(vy[i].y1 > ly && vy[i].y1 < ry)) return false;
        if(!(vy[i].z1 > lz && vy[i].z1 < rz)) return false;
    }
    return true;
}

void solve()
{
    v[0].clear();
    v[1].clear();
    v[2].clear();
    int n;
    scanf("%d",&n);
    int x1,y1,z1,x2,y2,z2;
    for(int i = 1; i <= n; i ++) {
        scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);
        if(x1 > x2) swap(x1,x2);
        if(y1 > y2) swap(y1,y2);
        if(z1 > z2) swap(z1,z2);
        if(x1 == x2) v[0].push_back(point(x1,y1,z1,x2,y2,z2));
        else if(y1 == y2) v[1].push_back(point(x1,y1,z1,x2,y2,z2));
        else v[2].push_back(point(x1,y1,z1,x2,y2,z2));
    }
    for(int i = 0; i < 3; i ++)
        if(v[i].size() == n) {
            cout << "NO" << endl;
            return;
        }
    bool x = check_xy(v[0],v[1]);
    bool y = check_xz(v[0],v[2]);
    bool z = check_yz(v[1],v[2]);
    if((x && y && (v[0].size() != 0)) || (y && z && (v[2].size() != 0)) || (x && z && (v[1].size() != 0))) cout << "YES" << endl;
    else cout << "NO" << endl;
}
            
int main()
{
    int t;
    scanf("%d",&t);
    while(t --) solve();
    return 0;
}

