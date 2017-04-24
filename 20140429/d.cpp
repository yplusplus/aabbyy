#include <bits/stdc++.h>
using namespace std;

char s[100010];

int cal(int n,int st,char a,char b)
{
	for(int i = 1; s[i]; i ++) {
		if(s[i] == a) {
			if(st + 1 <= n) st ++;
		}
		else if(s[i] == b) {
			if(st > 1) st --;
		}
	}
	return st;
}

int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	scanf("%s",s + 1);
	long long ans = 1;
	int c1 = cal(n,1,'r','l');
	int c2 = cal(n,n,'r','l');
	ans *= abs(c2 - c1) + 1;
	c1 = cal(m,1,'u','d');
	c2 = cal(m,m,'u','d');
	ans *= abs(c2 - c1) + 1;
	c1 = cal(k,1,'f','b');
	c2 = cal(k,k,'f','b');
	ans *= abs(c2 - c1) + 1;
	cout << ans << endl;
	return 0;
}
