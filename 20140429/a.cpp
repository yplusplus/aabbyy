#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
struct point
{
	int a,b,c,id;
	void read(int _id) {
		id = _id;
		scanf("%d%d%d",&a,&b,&c);
	}
}a[N],b[N],c[N];

bool cmpx(const point &p,const point &q)
{
	return p.a + p.b < q.a + q.b;
}

bool cmpy(const point &p,const point &q)
{
	return p.c + p.b > q.c + q.b;
}

long long A[N],B[N],C[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++)
		a[i].read(i);
	int c1 = 0,c2 = 0;
	for(int i = 1; i <= n; i ++)
		if(a[i].a < a[i].c) b[++ c1] = a[i];
		else c[++ c2] = a[i];
	sort(b + 1,b + c1 + 1,cmpx);
	sort(c + 1,c + c2 + 1,cmpy);
	int cc = 0;
	for(int i = 1; i <= c1; i ++) a[++ cc] = b[i];
	for(int i = 1; i <= c2; i ++) a[++ cc] = c[i];
	
	for(int i = 1; i <= n; i ++) {
		A[i] = A[i - 1] + a[i].a;
		B[i] = max(B[i - 1],A[i]) + a[i].b;
		C[i] = max(C[i - 1],B[i]) + a[i].c;
	}
	cout << C[n] << endl;
	for(int i = 1; i <= n; i ++)
		printf("%d ",a[i].id);
	cout << endl;
	return 0;
}
