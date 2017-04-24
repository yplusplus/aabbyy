#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <stack>
using namespace std;

int a[210][210];
int c[210 * 210];
stack<int> sta;
int visit[210 * 210 * 210];
char s[210 * 210][10];

bool check(int n)
{
	//cout << "123" << endl;
	int ct = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			a[i][j] = c[++ ct];
	while(!sta.empty()) sta.pop();
	bool flag = true;
	for(int i = 1; i <= n; i ++) {
		int sum = 0;
		for(int j = 1; j <= n; j ++) {
			sum += a[i][j];
		}
		if(visit[sum]) {
			flag = false;
			break;
		}
		sta.push(sum);
		visit[sum] = 1;
		sum = 0;
		for(int j = 1; j <= n; j ++) {
			sum += a[j][i];
		}
		if(visit[sum]) {
			flag = false;
			break;
		}
		sta.push(sum);
		visit[sum] = 1;
	}
	int sumx = 0,sumy = 0;
	for(int i = 1; i <= n; i ++) {
		sumx += a[i][i];
		sumy += a[i][n - i + 1];
	}
	//cout << "123" << endl;
	if(visit[sumx]) {
		flag = false;
	}
	else {
		visit[sumx] = 1;
		sta.push(sumx);
	}
	//cout << "123" << endl;
	if(visit[sumy]) {
		flag = false;
	}
	else {
		visit[sumy] = 1;
		sta.push(sumy);
	}
	//cout << "123" << endl;
	while(!sta.empty()) {
		visit[sta.top()] = 0;
		sta.pop();
	}
	//cout << "123" << endl;
	return flag;
}

void output(char *s)
{
	for(int i = 0; s[i]; i ++)
		putchar(s[i]);
}

void output(int n)
{
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= n; j ++) {
			output(s[a[i][j]]);
			if(j == n) printf("\n");
			else printf(" ");
		}
	}
}

void init()
{
	int ct = 0;
	for(int i = 1; i <= 200 * 200; i ++) {
		++ ct;
		int x = ct;
		int bit = 0;
		while(x) {
			s[ct][bit ++] = (x % 10) + '0';
			x /= 10;
		}
		s[ct][bit] = 0;
		reverse(s[ct],s[ct] + bit);
	}
}

int main()
{
	init();
	//freopen("out.txt", "w", stdout);
	srand(time(0));
	int t,n;
	scanf("%d",&t);
	//t = 200;
		memset(visit,0,sizeof(visit));
	for(int cas = 1; cas <= t; cas ++) {
		int ct = 0;
		scanf("%d",&n);
		//n = cas + 2;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++) {
				++ ct;
				c[ct] = ct;
			}
//		for(int i = 1; i <= ct; i ++) cout << c[i] << endl;
		bool flag = false;
		printf("Case #%d:\n",cas);
		while (1) {
		//for(int i = 1; i < 10; i ++) {
			random_shuffle(c + 1,c + ct + 1);
			if(check(n)) {
				output(n);
				break;
			}
			//else printf("Fuck\n");
		}
	}
	return 0;
}