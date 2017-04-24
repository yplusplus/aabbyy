#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

const int N = 810;
struct point
{
	char s[12],str[810][12];
}a[N],b[N];

map<string,int> ma1,ma2;
int aa[810][810],bb[810][810];
int mx[810],my[810],pos[810];

int main()
{
	int n;
	while(scanf("%d",&n) != EOF) {
		ma1.clear();
		ma2.clear();
		for(int i = 1; i <= n; i ++) {
			scanf("%s",a[i].s);
			ma1[a[i].s] = i;
			for(int j = 1; j <= n; j ++) {
				scanf("%s",a[i].str[j]);
			}
		}
		for(int i = 1; i <= n; i ++) {
			scanf("%s",b[i].s);
			ma2[b[i].s] = i;
			for(int j = 1; j <= n; j ++)
				scanf("%s",b[i].str[j]);
		}
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= n; j ++) {
				aa[i][j] = ma2[a[i].str[j]];
			}
		}
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++) {
				bb[i][ma1[b[i].str[j]]] = n - j + 1;
			}
		memset(mx,-1,sizeof(mx));
		memset(my,-1,sizeof(my));
		memset(pos,0,sizeof(pos));
		bool change = true;
		while(change) {
			change = false;
			for(int i = 1; i <= n; i ++) {
				while(mx[i] == -1) {
					change = true;
					int x = aa[i][++ pos[i]];
					if(my[x] == -1) {
						my[x] = i;
						mx[i] = x;
					}
					else {
						if(bb[x][i] > bb[x][my[x]]) {
							mx[my[x]] = -1;
							my[x] = i;
							mx[i] = x;
						}
					}
				}
			}
		}
		printf("YES\n");
		for(int i = 1; i <= n; i ++)
			printf("%s %s\n",a[i].s,b[mx[i]].s);
	}
	return 0;
}



