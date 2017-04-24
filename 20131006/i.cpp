
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 20010;
char s[N],str[N];
int c[N];
char ss[N];

int get_cost(int m,int len,bool f1,bool f2)
{
	int pos = -1;
	char now;
	int ansx = 0,ansy = 0;
	if(f2) {
		for(int i = 0; i < m; i ++) {
			if(i > pos) {
				ansx ++;
				pos = i + len - 1;
				now = str[i];
			}
			else {
				if(str[i] == now) continue;
				ansx ++;
				pos = i + len - 1;
				now = str[i];
			}
		}
	}
	if(f1) {
		reverse(str,str + m);
		pos = -1;
		for(int i = 0; i < m; i ++) {
			if(i > pos) {
				ansy ++;
				pos = i + len - 1;
				now = str[i];
			}
			else {
				if(str[i] == now) continue;
				ansy ++;
				pos = i + len - 1;
				now = str[i];
			}
		}
	}
	if(f1 && f2) return min(ansx,ansy);
	if(f1) return ansy;
	if(f2) return ansx;
}

int main()
{
	int t,n,m;
	scanf("%d",&t);
	while(t --) {
		scanf("%d%d",&n,&m);
		scanf("%s",s);
		int i = 0;
		memset(c,0,sizeof(c));
		int cnt = 0;
		while(i < n) {
			int j = i;
			while(j < n && s[j] == s[i]) {
				c[cnt] ++;
				j ++;
			}
			ss[cnt ++] = s[i];
			i = j;
		}
		bool flag = false;
		for(i = 0; i < cnt; i ++)
			if(c[i] >= m) {
				flag = true;
				break;
			}
		if(!flag) {
			printf("-1\n");
			continue;
		}
		int ans = 0;
		i = 0;
		while(i < cnt) {
			while(i < cnt && c[i] >= m) {
				ans += (c[i] % m == 0 ? c[i] / m : c[i] / m + 1);
				i ++;
			}
			if(i == cnt) break;
			int ct = 0;
			int j = i;
			while(j < cnt && c[j] < m) {
				for(int k = 0; k < c[j]; k ++) {
					str[ct ++] = ss[j];
				}
				j ++;
			}
			str[ct] = 0;
			bool f1 = false;
			bool f2 = false;
			if(i) f1 = true;
			if(j < cnt) f2 = true;
			ans += get_cost(ct,m,f1,f2);
			i = j;
		}
		printf("%d\n",ans);
	}
	return 0;
}

