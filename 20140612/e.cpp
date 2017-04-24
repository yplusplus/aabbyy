#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
char s[55];
int base;
char str[N];
int a[N];
int dp[N][100];
int prex[N][100],prey[N][100];
int score(char c)
{
	if(isdigit(c)) return c - '0';
	return c - 'A' + 10;
}

int convert()
{
	int b[N];
	memset(b,0,sizeof(b));
	int n = strlen(str);
	for(int i = 0; i < n; i ++) {
		b[i] = str[n - i - 1] - '0';
		assert(b[i] >= 0 && b[i] <= '9');
	}
	int cnt = 0;
	while(1) {
		bool flag = false;
		for(int i = 0; i < n; i ++) {
			if(b[i]) flag = true;
		}
		if(!flag) break;
		int tmp = 0;
		for(int i = n - 1; i >= 0; i --) {
			int p = (tmp * 10 + b[i]) % base;
			b[i] = (tmp * 10 + b[i]) / base;
			tmp = p;
		}
		a[++ cnt] = tmp;
	}
	reverse(a + 1,a + cnt + 1);
//	cout << cnt << " : "; 
//	for(int i = 1; i <= cnt; i ++) cout << a[i];
//	cout << endl;
	return cnt;
}

int cc = 0,ans[N];

void get_ans(int dep,int x)
{
	if(dep == 0) return;
	get_ans(dep - 1,prey[dep][x]);
	ans[++ cc] = prex[dep][x];
}

int main()
{	
	freopen("digits.in","r",stdin);
	freopen("digits.out","w",stdout);
	scanf("%d",&base);
	scanf("%s",s);
	scanf("%s",str);
	int n = convert();
	dp[0][0] = 1;
	for(int i = 0; i <= 500; i ++) {
		for(int j = 0; j < 100; j ++) {
			if(!dp[i][j]) continue;
			int x = j * base + a[i];
			for(int k = 0; s[k]; k ++) {
				int y = score(s[k]);
				if(x - y >= 100 || x < y) continue;
				dp[i + 1][x - y] += dp[i][j];
				prex[i + 1][x - y] = k;
				prey[i + 1][x - y] = j;
				if(dp[i + 1][x - y] > 10) dp[i + 1][x - y] = 10;
			}
		}
	}
	int tot = 0;
	int id = -1;
	bool flag = false;
	for(int i = n + 1; i <= n + 1; i ++) {
		if(dp[i][0]) {
			flag = true;
			id = i;
			tot += dp[i][0];
			if(tot > 10) tot = 10;
		}
	}
	if(!flag) {
		puts("Impossible");
		return 0;
	}
	if(tot == 1) {
		puts("Unique");
	}
	else puts("Ambiguous");
	get_ans(id,0);
	for(int i = 1; i <= cc; i ++) {
		if(ans[i]) {
			for(int j = i; j <= cc; j ++)
				printf("%c",s[ans[j]]);
			printf("\n");
			break;
		}
	}
	return 0;
}
