#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

const int N = 100010;
struct point
{
	int val,idx;
	friend bool operator < (const point &p,const point &q) {
		return p.val < q.val;
	}
	point() {}
	point(int val,int idx):val(val),idx(idx) {}
};
set<point> st;

int c[N];

bool check_up(int n,int a[])
{
	for(int i = 2; i <= n; i ++)
		if(a[i] < a[i - 1]) return false;
	return true;
}

bool check_down(int n,int a[])
{
	for(int i = 2; i <= n; i ++)
		if(a[i] > a[i - 1]) return false;
	return true;
}

bool flag;

bool up(int n)
{
	int ans1[N],ans2[N],c1 = 0,c2 = 0;
	for(int i = 1; i <= n; i ++) {
		if(!c1) ans1[++ c1] = c[i];
		else if(c[i] < ans1[c1]) {
			if(!c2) ans2[++ c2] = c[i];
			else if(c[i] < ans2[c2]) return false;
			else ans2[++ c2] = c[i];
		}
		else ans1[++ c1] = c[i];
	}
	if(!c2) {
		printf("1 %d\n",n - 1);
		printf("%d\n",ans1[1]);
		for(int i = 2; i <= n; i ++) {
			printf("%d",ans1[i]);
			if(i == n) printf("\n");
			else printf(" ");
		}
	}
	else {
		printf("%d %d\n",c1,c2);
		for(int i = 1; i <= c1; i ++) {
			printf("%d",ans1[i]);
			if(i == c1) printf("\n");
			else printf(" ");
		}
		for(int i = 1; i <= c2; i ++) {
			printf("%d",ans2[i]);
			if(i == c2) printf("\n");
			else printf(" ");
		}
	}
	return flag = true;
}

bool down(int n)
{
	int ans1[N],ans2[N],c1 = 0,c2 = 0;
	for(int i = 1; i <= n; i ++) {
		if(!c1) ans1[++ c1] = c[i];
		else if(c[i] > ans1[c1]) {
			if(!c2) ans2[++ c2] = c[i];
			else if(c[i] > ans2[c2]) return false;
			else ans2[++ c2] = c[i];
		}
		else ans1[++ c1] = c[i];
	}
	if(!c2) {
		printf("1 %d\n",n - 1);
		printf("%d\n",ans1[1]);
		for(int i = 2; i <= n; i ++) {
			printf("%d",ans1[i]);
			if(i == n) printf("\n");
			else printf(" ");
		}
	}
	else {
		printf("%d %d\n",c1,c2);
		for(int i = 1; i <= c1; i ++) {
			printf("%d",ans1[i]);
			if(i == c1) printf("\n");
			else printf(" ");
		}
		for(int i = 1; i <= c2; i ++) {
			printf("%d",ans2[i]);
			if(i == c2) printf("\n");
			else printf(" ");
		}
	}
	return flag = true;
}

int visit[N];
bool up_down(int n)
{
	int ans1[N],ans2[N],c1 = 0,c2 = 0;
	ans1[++ c1] = c[1];
	for(int i = 2; i <= n; i ++) {
		if(ans1[c1] > c[i]) {
		       if(!c2) ans2[++ c2] = c[i];
		       else if(ans2[c2] < c[i]) return false;
		       else ans2[++ c2] = c[i];	   
		}
		else {
			if(i == n) ans1[++ c1] = c[i];
			else if(c[i] > c[i + 1]) {
				if(!c2) ans2[++ c2] = c[i];
				else if(ans2[c2] > c[i]) ans2[++ c2] = c[i];
				else ans1[++ c1] = c[i];
			}
			else ans1[++ c1] = c[i];
		}
	}
		printf("%d %d\n",c1,c2);
		for(int i = 1; i <= c1; i ++) {
			printf("%d",ans1[i]);
			if(i == c1) printf("\n");
			else printf(" ");
		}
		for(int i = 1; i <= c2; i ++) {
			printf("%d",ans2[i]);
			if(i == c2) printf("\n");
			else printf(" ");
		}


	return flag = true;
}

bool down_up(int n)
{
	for(int i = 1; i <= n; i ++) c[i] = n + 1 - c[i];
	int ans1[N],ans2[N],c1 = 0,c2 = 0;
	ans1[++ c1] = c[1];
	for(int i = 2; i <= n; i ++) {
		if(ans1[c1] > c[i]) {
		       if(!c2) ans2[++ c2] = c[i];
		       else if(ans2[c2] < c[i]) return false;
		       else ans2[++ c2] = c[i];	   
		}
		else {
			if(i == n) ans1[++ c1] = c[i];
			else if(c[i] > c[i + 1]) {
				if(!c2) ans2[++ c2] = c[i];
				else if(ans2[c2] > c[i]) ans2[++ c2] = c[i];
				else ans1[++ c1] = c[i];
			}
			else ans1[++ c1] = c[i];
		}
	}
		printf("%d %d\n",c1,c2);
		for(int i = 1; i <= c1; i ++) {
			printf("%d",n + 1 - ans1[i]);
			if(i == c1) printf("\n");
			else printf(" ");
		}
		for(int i = 1; i <= c2; i ++) {
			printf("%d",n + 1 - ans2[i]);
			if(i == c2) printf("\n");
			else printf(" ");
		}
	return flag = true;
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++)
		scanf("%d",&c[i]);
	flag = false;
	up(n);
	if(flag) return 0;
	down(n);
	if(flag) return 0;
	up_down(n);
	if(flag) return 0;
	down_up(n);
	if(flag) return 0;
	printf("Fail\n");
	return 0;
}

