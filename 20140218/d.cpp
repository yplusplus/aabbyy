#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
struct road
{
	string s1,s2;
	int type;
	int len;
	vector<int> v;
	void init() {
		v.clear();
	}
	void read() {
		cin >> s1 >> s2;
		string s;
		cin >> s;
		if(s[0] == 'r') type = 0;
		else type = 1;
		cin >> len;
		if(type) {
			int tot,x;
			cin >> tot;
			while(tot --) {
				cin >> x;
				v.push_back(x);
			}
		}
	}
}a[10010];

double cal(int n,double speed)
{
	double nowT = 0;
	for(int i = 1; i <= n; i ++) {
		if(a[i].type) {
			int tmp = ((int)((eps + nowT))) * 3600;
			double T = nowT * 3600 - tmp;
			int times = ceil(T - eps);
			bool flag = false;
			for(int j = 0; j < a[i].v.size(); j ++) {
				if(times <= a[i].v[j] * 60) {
					flag = true;
					nowT = (int)(nowT + eps) + a[i].v[j] / 60.0 + a[i].len / 60.0;
					break;
				}
			}
			if(!flag) {
				nowT = (int)(nowT + eps) + 1 + a[i].v[0] / 60.0 + a[i].len / 60.0;
			}
		}
		else {
			if(fabs(speed) < eps) return 1e20;
			nowT += a[i].len / speed;
		}
		//if(n== 2 && fabs(speed) < eps) cout << nowT << endl;
	}
	return nowT;
}

void solve(int n,int cas)
{
	double T = 0,speed = 80;
	for(int i = 1; i <= n; i ++) {
		a[i].init();
		a[i].read();
	}
	double time_init = cal(n,80);
	double lt = 0,rt = 80,mid,ans = 80;
	for(int i = 1; i <= 80; i ++) {
		mid = (lt + rt) / 2;
		if(fabs(cal(n,mid) - time_init) < eps) {
			ans = mid;
			rt = mid;
		}
		else lt = mid;
	}
	int h = (int)(time_init + eps);
	time_init -= h;
	int tot = (int)((time_init + eps) * 3600);
	if(tot == 3600) h ++,tot = 0;
	int m = tot / 60;
	int s = tot % 60;
	printf("Test Case %d: %02d:%02d:%02d %.2lf\n",cas,h,m,s,ans);
}

int main()
{
//	ios::sync_with_stdio(0);
	int n;
	int cas = 0;
	while(cin >> n,n != 0) {
		solve(n,++ cas);
		printf("\n");
	}
	return 0;
}
