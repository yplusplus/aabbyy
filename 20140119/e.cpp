#include <bits/stdc++.h>
using namespace std;

int visit[155][155];
int dep = 0;
void dfs(int n,int m)
{
	if(n == m) return;
	dep ++;
	if(dep > 40000) return;
	if(n > m) dfs(n - m,2 * m);
	else dfs(n * 2,m - n);
}

void cal(int n,int m,double &ept,double &p)
{
	if(n == m) {
		ept = 1;
		p = 0.5;
		return;
	}
	if(n >= m) {
		double tept,tp;
		cal(n - m,2 * m,tept,tp);
		ept = 1 + 0.5 * tept;
		p = 0.5 + 0.5 * tp;
	}
	else {
		double tept,tp;
		cal(n * 2,m - n,tept,tp);
		ept = 1 + 0.5 * tept;
		p = 0.5 * tp;
	}
}

int main()
{
	int t,n,m;
	int Case = 1;
	cin >> t;
	while(t --) {
		cin >> n >> m;
		printf("Case %d: ", Case++);
		memset(visit,0,sizeof(visit));
		dep = 0;
		dfs(n,m);
		if(dep < 40000) {
			double ept,p;
			cal(n,m,ept,p);
			printf("%.6lf %.6lf\n",ept,p);
		}
		else {
			printf("%.6lf %.6lf\n",2.0,1.0 * n / (n + m));
		}
	}
	return 0;
}

