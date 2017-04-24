#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//note : [L,R)
const int N = 300010;
int mapL[N * 4],mapR[N * 4];
bool flag[N * 4];
double sum[N * 4],ad1[N * 4],val[N * 4];
double times1[N * 4];
int c[N];

void set(int step)
{
	flag[step] = true;
	sum[step] = 0;
	ad1[step] = 0;
	//   ad2[step] = 0;
	val[step] = 0;
	times1[step] = 0;
}

int dis(int step)
{
	return c[mapR[step]] - c[mapL[step]];
}

void init(int lt,int rt,int step)
{
	mapL[step] = lt;
	mapR[step] = rt;
	if(lt + 1 == rt) return;
	int mid = (lt + rt) / 2;
	init(lt,mid,2 * step);
	init(mid,rt,2 * step + 1);
}

void add_val(int step,double add)
{
	val[step] += add;
	sum[step] += dis(step) * add;
}

void add_ad1(int step,double add,double times)
{
	times1[step] += times;
	ad1[step] += add;
	sum[step] += add * dis(step) + times * 1.0 * dis(step) / 2.0 * (dis(step) - 1);
}

/*
   void add_ad2(int step,double add,double times)
   {
   times2[step] += times;
   ad2[step] += add;
   sum[step] += add * dis(step) - 1.0 * times * dis(step) / 2.0 * (dis(step) - 1);
   }
 */

void down(int step)
{
	if(flag[step]) {
		set(2 * step);
		set(2 * step + 1);
		flag[step] = false;
	}


	add_val(2 * step,val[step]);
	add_val(2 * step + 1,val[step]);
	val[step] = 0;



	add_ad1(2 * step,ad1[step],times1[step]);
	add_ad1(2 * step + 1,ad1[step] + 1.0 * times1[step] * dis(2 * step),times1[step]);
	ad1[step] = 0;
	times1[step] = 0;

	/*

	   add_ad2(2 * step,ad2[step],times2[step]);
	   add_ad2(2 * step + 1,ad2[step] - 1.0 * times2[step] * dis(2 * step),times2[step]);
	   ad2[step] = 0;
	   times2[step] = 0;
	 */

}

void set(int lt,int rt,int step)
{
	if(mapL[step] == lt && mapR[step] == rt) {
		set(step);
		return;
	}
	down(step);
	if(rt <= mapR[2 * step]) set(lt,rt,2 * step);
	else if(lt >= mapR[2 * step]) set(lt,rt,2 * step + 1);
	else {
		//int mid = (lt + rt) / 2;
		set(lt,mapR[2 * step],2 * step);
		set(mapR[2 * step],rt,2 * step + 1);
	}
	sum[step] = sum[2 * step] + sum[2 * step + 1];
}

void add1(int lt,int rt,int step,double val,double times)
{
	if(mapL[step] == lt && mapR[step] == rt) {
		add_ad1(step,val,times);
		return;
	}
	down(step);
	if(rt <= mapR[2 * step]) add1(lt,rt,2 * step,val,times);
	else if(lt >= mapR[2 * step]) add1(lt,rt,2 * step + 1,val,times);
	else {
		//int mid = (lt + rt) / 2;
		add1(lt,mapR[2 * step],2 * step,val,times);
		add1(mapR[2 * step],rt,2 * step + 1,val + times * (c[mapR[2 * step]] - c[lt]),times);
	}
	sum[step] = sum[2 * step] + sum[2 * step + 1];
}

/*
   void add2(int lt,int rt,int step,double val,double times)
   {
   if(mapL[step] == lt && mapR[step] == rt) {
   add_ad2(step,val,times);
   return;
   }
   down(step);
   if(rt <= mapR[2 * step]) add2(lt,rt,2 * step,val,times);
   else if(lt >= mapR[2 * step]) add2(lt,rt,2 * step + 1,val,times);
   else {
//int mid = (lt + rt) / 2;
add2(lt,mapR[2 * step],2 * step,val,times);
add2(mapR[2 * step],rt,2 * step + 1,val - times * (c[mapR[2 * step]] - c[lt]),times);
}
sum[step] = sum[2 * step] + sum[2 * step + 1];
}*/

void add(int lt,int rt,int step,double val)
{
	if(mapL[step] == lt && mapR[step] == rt) {
		add_val(step,val);
		return;
	}
	down(step);
	if(rt <= mapR[2 * step]) add(lt,rt,2 * step,val);
	else if(lt >= mapR[2 * step]) add(lt,rt,2 * step + 1,val);
	else {
		//int mid = (lt + rt) / 2;
		add(lt,mapR[2 * step],2 * step,val);
		add(mapR[2 * step],rt,2 * step + 1,val);
	}
	sum[step] = sum[2 * step] + sum[2 * step + 1];    
}

double query(int lt,int rt,int step)
{
	if(mapL[step] == lt && mapR[step] == rt) return sum[step];
	down(step);
	if(rt <= mapR[2 * step]) return query(lt,rt,2 * step);
	else if(lt >= mapR[2 * step]) return query(lt,rt,2 * step + 1);
	else {
		//int mid = (lt + rt) / 2;
		return query(lt,mapR[2 * step],2 * step) + query(mapR[2 * step],rt,2 * step + 1);
	}
}

struct point
{
	int cd,x,y,t,id;
	point() {}
	point(int cd,int x,int y,int t,int id):cd(cd),x(x),y(y),t(t),id(id) {}
}a[N / 3 + 10];

bool cmp(const point &p,const point &q)
{
	return p.id < q.id;
}

int cnt = 0;

int find(int x)
{
	int lt = 1,rt = cnt,mid;
	while(lt <= rt) {
		mid = (lt + rt) / 2;
		if(c[mid] == x) return mid;
		if(c[mid] > x) rt = mid - 1;
		else lt = mid + 1;
	}
}

int main()
{
	memset(flag,false,sizeof(flag));
	memset(sum,0,sizeof(sum));
	memset(val,0,sizeof(val));
	memset(ad1,0,sizeof(ad1));
	memset(times1,0,sizeof(times1));
	//memset(ad2,0,sizeof(ad2));
	//memset(times2,0,sizeof(times2));
	int n,m,r;
	scanf("%d%d%d",&n,&r,&m);
	char s[15];
	int T,x,y;

	for(int i = 1; i <= m; i ++) {
		scanf("%d%s",&T,s);
		scanf("%d%d",&x,&y);
		if(s[0] == 's') {
			a[i] = point(0,x,y + 1,T,i);
			c[++ cnt] = x;
			c[++ cnt] = y + 1;
		}
		else {
			a[i] = point(1,x,y,T,i);
			c[++ cnt] = x - y + 1;
			c[++ cnt] = x + 1;
			c[++ cnt] = x + y; 
		}
	}
	sort(c + 1,c + cnt + 1);
	int tmp = 1;
	for(int i = 2; i <= cnt; i ++)
		if(c[tmp] != c[i]) c[++ tmp] = c[i];
	cnt = tmp;
	init(1,cnt,1);
	int nowT = 0;
	double save = 0;
	for(int i = 1; i <= m; i ++) {
		add(1,cnt,1,1.0 * r * (a[i].t - nowT));
		nowT = a[i].t;
		if(a[i].cd == 0) {
			x = find(a[i].x);
			y = find(a[i].y);
			save += query(x,y,1);
			set(x,y,1);
			printf("%.20lf\n",save);
		}
		else {

			x = a[i].x;
			y = a[i].y;
			double times = save / y / y;;
			add1(find(x - y + 1),find(x + 1),1,times,times);
			if(y > 1) add1(find(x + 1),find(x + y),1,(y - 1) * times,-times);
			save = 0;
		}

	}
	return 0;
}

