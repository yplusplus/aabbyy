#include <bits/stdc++.h>
using namespace std;

int leap(int x)
{
	return x % 400 == 0 || (x % 100 != 0 && x % 4 == 0);
}

int year[2][13] = {0,31,28,31,30,31,30,31,31,30,31,30,31,
	               0,31,29,31,30,31,30,31,31,30,31,30,31};

struct point
{
	int x,y,z;
	point() {}
	point(int x,int y,int z):x(x),y(y),z(z) {}
	void output() {
		printf("%d-%02d-%02d\n",x,y,z);
	}
}a[10010 * 370];

int mapx[10010][13][32];

void init()
{
	int x = 1582,y = 10,z = 4;
	for(int i = 0; ; i ++) {
		if(x >= 10000) break;
		mapx[x][y][z] = i;
		z ++;
		int leap = (x % 4 == 0 ? 1 : 0);
		if(z > year[leap][y]) {
			y ++;
			z = 1;
			if(y > 12) x ++,y = 1;
		}
	}
	x = 1582,y = 10,z = 15;
	for(int i = 0; ; i ++) {
		if(x > 10000) break;
		a[i] = point(x,y,z);
		z ++;
		int lp = leap(x);
		if(z > year[lp][y]) {
			y ++;
			z = 1;
			if(y > 12) x ++,y = 1;
		}
	}
}
	
int main()
{
	init();
	int x,y,z;
	while(scanf("%d-%d-%d",&x,&y,&z) != EOF) a[mapx[x][y][z]].output();
	return 0;
}
