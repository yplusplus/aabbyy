#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 300010;
int visit[26];
char s[N];
int fac[300010];
int ans[N];

int main()
{
	int n;
	scanf("%d",&n);
	if(n <= 26) {
		for(int i = 0; i < n; i ++)
			printf("%c",i + 'a');
		printf("\n");
		return 0;
	}
	int cnt = 0;
	for(int i = 1; i * i <= n; i ++) {
		if(n % i == 0) {
			fac[cnt ++] = i;
			fac[cnt ++] = n / i;
		}
	}
	memset(ans,-1,sizeof(ans));
	for(int i = 0; i < n; i ++) {
		memset(visit,0,sizeof(visit));
		for(int j = 0; j < cnt; j ++) {
			int x = i - fac[j];
			if(x < 0) x += n;
			if(x < i) visit[ans[x]] ++;
			x = i + fac[j];
			if(x >= n) x -= n;
			if(x < i) visit[ans[x]] ++;
			//if(i == 2) cout << x << " " << fac[j] << endl;
		}
		for(int j = 0; j < 26; j ++) {
			if(!visit[j]) {
				ans[i] = j;
				break;
			}
		}
		if(ans[i] == -1) {
			printf("Impossible\n");
			return 0;
		}
	}
	for(int i = 0; i < n; i ++)
		printf("%c",ans[i] + 'a');
	printf("\n");
	return 0;
}

