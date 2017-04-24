#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct point
{
    int x,y;
    point() {}
    point(int x,int y):x(x),y(y) {}
}a[1000010];

int tot = 0;
int map[2010][2010];
void cal(int x,int y)
{
    while(y) {
        a[++ tot] = point(x,y);
        map[x][y] = tot;
        x ++, y --;
    }
}

void init()
{
    for(int i = 1; tot <= 500000; i ++) {
        cal(1,i);
    }
}
    
    
int main()
{
    init();
    int n,x,y;
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++) {
        scanf("%d%d",&x,&y);
        printf("%d\n",map[a[x].x + a[y].x][a[x].y + a[y].y]);
    }
    return 0;
}


