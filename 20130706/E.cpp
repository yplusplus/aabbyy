#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

const int N = 25;
struct point 
{
	int x,y;
	point() {}
	point(int x,int y):x(x),y(y) {}
}a[N];

int sig(int x)
{
	if(x > 0) return 1;
	if(x == 0) return 0;
	return -1;
}

int dot(point o,point a,point b)
{
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

int cross(point o,point a,point b)
{
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

bool onSeg(point p,point a,point b)
{
	return sig(cross(p,a,b)) == 0 && sig(dot(p,a,b)) <= 0;
}

int inpolygon(point *ps,int n,point p)
{
	int cnt = 0;
	ps[n] = ps[0];
	for(int i = 0; i < n; i ++) {
		if(onSeg(p,ps[i],ps[i + 1])) return 2;
		int k = sig(cross(ps[i],ps[i + 1],p));
		int d1 = sig(ps[i + 0].y - p.y);
		int d2 = sig(ps[i + 1].y - p.y);
		if(k > 0 && d1 <= 0 && d2 > 0) cnt ++;
		if(k < 0 && d2 <= 0 && d1 > 0) cnt --;
	}
	return cnt != 0;
}

int main()
{
	int n,A,B;
	double px,py,qx,qy;
	while(scanf("%lf%lf%lf%lf",&px,&py,&qx,&qy) != EOF) {
		scanf("%d%d%d",&n,&A,&B);
		int min_x = qx + 1,min_y = qy + 1,max_x = px - 1,max_y = py - 1;
		for(int i = 0; i < n; i ++) {
			scanf("%d%d",&a[i].x,&a[i].y);
			min_x = min(a[i].x,min_x);
			max_x = max(a[i].x,max_x);
			min_y = min(a[i].y,min_y);
			max_y = max(a[i].y,max_y);
		}
		/*
		//assert
		if(!(min_x >= 0 && max_x <= 500 && min_y >= 0 && max_y <= 500)) return 0;
		if(!(n >= 3 && n <= 20)) return 0;
		*/
		double sum = 0;
		for(int i = min_x; i <= max_x; i ++)
			for(int j = min_y; j <= max_y; j ++) {
				if(!inpolygon(a,n,point(i,j))) continue;
				double lx = max(0.0 + px,i - 0.5),rx = min(0.0 + qx,i + 0.5);
				double ly = max(0.0 + py,j - 0.5),ry = min(0.0 + qy,j + 0.5);
				sum += (rx - lx) * (ry - ly) * (A * i + B * j);
			}
		sum /= (qy - py) * (qx - px);
		printf("%.3lf\n",sum);
	}
	return 0;
}
