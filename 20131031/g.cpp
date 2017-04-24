#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

const int N = 70010;
char s[N][10];
long long f[10];
int n;
int cmp(char *s,char *str)
{
	int ans = 0;
	for(int i = 0; i < 4; i ++)
		if(s[i] != str[i]) ans ++;
	return ans;
}

void solve(int nn)
{
	set<int> st;
	int a[10];
	int ct = 0;
	int m = nn;
	while(nn) {
		a[ct ++] = nn % 10;
		nn /= 10;
	}
	for(int i = 0; i < ct; i ++) {
		for(int j = 0; j < 10; j ++) {
			if(j == a[i]) continue;
			if(i == ct - 1 && !j) continue;
			int x = 0;
			for(int k = ct - 1; k >= 0; k --) {
				if(k == i) x = 10 * x + j;
				else x = 10 * x + a[k];
			}
			if(m < x && x <= n && !st.count(x)) {
				f[cmp(s[m],s[x])] ++;
				st.insert(x);
//				cout << m << " " << x << endl;
			}
		}
	}
	for(int i = 0; i < ct && ct > 1; i ++) {
		if(i == ct - 1 && a[i - 1] == 0) continue;
		int x = 0;
		for(int k = ct - 1; k >= 0; k --) {
			if(k == i) continue;
			x = 10 * x + a[k];
		}
		if(m < x && x <= n && !st.count(x)) {
			st.insert(x);
			f[cmp(s[m],s[x])] ++;
		}
	}
	for(int i = 0; i <= ct; i ++) {
		for(int j = 0; j < 10; j ++) {
			if(i == ct && j == 0) continue;
			int x;
			if(i == ct) x = j;
			else x = 0;
			for(int k = ct - 1; k >= i; k --)
				x = 10 * x + a[k];
			if(i != ct) x = 10 * x + j;
			for(int k = i - 1; k >= 0; k --)
				x = 10 * x + a[k];
			if(m < x && x <= n && !st.count(x)) {
				st.insert(x);
				f[cmp(s[m],s[x])] ++;
//				cout << m << " " << x << endl;
			}
		}
	}
}

int main()
{
	scanf("%d",&n);
	memset(f,0,sizeof(f));
	for(int i = 1; i <= n; i ++) {
		scanf("%s",s[i]);
	}
	for(int i = 1; i <= n; i ++) {
		solve(i);
	}
	for(int i = 1; i <= 4; i ++) {
		cout << f[i];
		if(i == 4) cout << endl;
		else cout << " ";
	}
	return 0;
}

