#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

const int N = 2010;
struct point
{
    int x,y;
    point() {}
    point(int x,int y):x(x),y(y) {}
    void read() {
        scanf("%d%d",&x,&y);
    }
}a[N];
vector<point> v[N];

bool cmpx(const point &p,const point &q)
{
    if(p.x != q.x) return p.x < q.x;
    return p.y < q.y;
}

bool cmpy(const point &p,const point &q)
{
    if(p.y != q.y) return p.y < q.y;
    return p.x < q.x;
}

void processx(int id)
{
    sort(v[id].begin(),v[id].end(),cmpx);
    vector<point> tmp;
    int miny = 0x7fffffff;
    for(int i = 0; i < v[id].size(); i ++) {
        if(v[id][i].y >= miny) continue;
        if(1LL * v[id][i].x * v[id][i].y > 1000000000) continue;
        miny = v[id][i].y;
        tmp.push_back(v[id][i]);
    }
    v[id].clear();
    for(int i = 0; i < tmp.size(); i ++)
        v[id].push_back(tmp[i]);
    tmp.clear();
}

void processy(int id)
{
    sort(v[id].begin(),v[id].end(),cmpy);
    vector<point> tmp;
    int minx = 0x7fffffff;
    for(int i = 0; i < v[id].size(); i ++) {
        if(v[id][i].x >= minx) continue;
        if(1LL * v[id][i].x * v[id][i].y > 1000000000) continue;
        minx = v[id][i].x;
        tmp.push_back(v[id][i]);
    }
    v[id].clear();
    for(int i = 0; i < tmp.size(); i ++)
        v[id].push_back(tmp[i]);
    tmp.clear();
}

void unions1(int x,int y,int id)
{
    sort(v[x].begin(),v[x].end(),cmpy);
    sort(v[y].begin(),v[y].end(),cmpy);
    v[id].clear();
    for(int i = 0; i < v[x].size(); i ++) {
        int lt = 0,rt = v[y].size() - 1,mid,xx = -1;
        while(lt <= rt) {
            mid = (lt + rt) / 2;
            if(v[y][mid].y <= v[x][i].y) xx = mid,lt = mid + 1;
            else rt = mid - 1;
        }
        if(xx != -1) v[id].push_back(point(v[x][i].x + v[y][xx].x,v[x][i].y));
    }
    swap(x,y);
    for(int i = 0; i < v[x].size(); i ++) {
        int lt = 0,rt = v[y].size() - 1,mid,xx = -1;
        while(lt <= rt) {
            mid = (lt + rt) / 2;
            if(v[y][mid].y <= v[x][i].y) xx = mid,lt = mid + 1;
            else rt = mid - 1;
        }
        if(xx != -1) v[id].push_back(point(v[x][i].x + v[y][xx].x,v[x][i].y));
    }
    processy(id);
}

void unions2(int x,int y,int id)
{
    sort(v[x].begin(),v[x].end(),cmpx);
    sort(v[y].begin(),v[y].end(),cmpx);
    v[id].clear();
    for(int i = 0; i < v[x].size(); i ++) {
        int lt = 0,rt = v[y].size() - 1,mid,xx = -1;
        while(lt <= rt) {
            mid = (lt + rt) / 2;
            if(v[y][mid].x <= v[x][i].x) xx = mid,lt = mid + 1;
            else rt = mid - 1;
        }
        if(xx != -1) v[id].push_back(point(v[x][i].x,v[x][i].y + v[y][xx].y));
    }
    swap(x,y);
    for(int i = 0; i < v[x].size(); i ++) {
        int lt = 0,rt = v[y].size() - 1,mid,xx = -1;
        while(lt <= rt) {
            mid = (lt + rt) / 2;
            if(v[y][mid].x <= v[x][i].x) xx = mid,lt = mid + 1;
            else rt = mid - 1;
        }
        if(xx != -1) v[id].push_back(point(v[x][i].x,v[x][i].y + v[y][xx].y));
    }    
    processx(id);
}

stack<int> sta;
int main()
{
    int n,t;
    char s[15];
    scanf("%d",&t);
    while(t --) {
        while(!sta.empty()) sta.pop();
        scanf("%d",&n);
        for(int i = 0; i < N; i ++) v[i].clear();
        for(int i = 1; i <= n; i ++)
            a[i].read();
        for(int i = 1; i <= 2 * n - 1; i ++) {
            scanf("%s",s);
            if(isdigit(s[0])) {
                sta.push(i);
                int x;
                sscanf(s,"%d",&x);
                v[i].push_back(point(a[x]));
                if(a[x].x != a[x].y) {
                    swap(a[x].x,a[x].y);
                    v[i].push_back(point(a[x]));
                }
                sort(v[i].begin(),v[i].end(),cmpx);
            }
            else if(s[0] == 'V') {
                int x = sta.top();
                sta.pop();
                int y = sta.top();
                sta.pop();
                unions1(x,y,i);
                sta.push(i);
            }
            else {
                int x = sta.top();
                sta.pop();
                int y = sta.top();
                sta.pop();
                unions2(x,y,i);
                sta.push(i);
            }
        }
        long long ans = 1LL << 60;
        int x = sta.top();
        for(int i = 0; i < v[x].size(); i ++)
            ans = min(ans,1LL * v[x][i].x * v[x][i].y); 
        printf("%lld\n",ans);
    }
    return 0;
}




