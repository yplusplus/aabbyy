#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int M = 100010;
char sf[N][M],pf[N][M];
int nxt[M];
char str[M];

int get_next(int m)
{
//	cout << "enter" << endl;
	nxt[0] = -1;
	int i = 1,j = 0;
	while(i <= m) {
		if(j == -1 || str[i] == str[j]) {
			i ++,j ++;
			nxt[i] = j;
		}
		else j = nxt[j];
	}
//	cout << "over" << endl;
}

int m;
int kmp(char *s)
{
	int n = strlen(s);
	//m = strlen(str);
	//get_next(m);
	int i = 0,j  = 0;
	int ans = 0;
	while(i < n) {
		if(j == -1 || s[i] == str[j]) i ++,j ++;
		else j = nxt[j];
		if(j == m) {
			ans ++;
			j = nxt[j];
		}
	}
	return ans;
}

char tmp[M * 10];
int len;
int unions(char *s,char *str)
{
	int cc = 0;
	for(int i = 0; s[i]; i ++) tmp[cc ++] = s[i];
	for(int i = 0; str[i]; i ++) tmp[cc ++] = str[i];
	tmp[cc] = 0;
	return kmp(tmp);
}

int main()
{
	int cas = 0,n;
	while(scanf("%d",&n) != EOF) {
		scanf("%s",str);
		len = strlen(str);
		m = len;
		get_next(m);
		sf[0][0] = pf[0][0] = '0';
		sf[1][0] = pf[1][0] = '1';
		sf[1][1] = pf[1][1] = sf[1][1] = pf[1][1] = 0;
		printf("Case %d: ",++ cas);
		if(n == 0) cout << kmp(sf[0]) << endl;
		else if(n == 1) cout << kmp(sf[1]) << endl;
		else {
//			cout << "enter" << endl;
			long long ans[110];
			ans[0] = kmp(sf[0]);
			ans[1] = kmp(sf[1]);
			if(len == 1) {
				for(int i = 2; i <= n; i ++) ans[i] = ans[i - 1] + ans[i - 2];
				printf("%lld\n",ans[n]);
				continue;
			}
//			cout << "oer" << endl;
			for(int i = 2; i <= n; i ++) {
				ans[i] = unions(sf[i - 1],pf[i - 2]) + ans[i - 1] + ans[i - 2];
				int cc = 0;
				for(int j = 0; pf[i - 1][j] && cc < len - 1; j ++) pf[i][cc ++] = pf[i - 1][j];
				for(int j = 0; pf[i - 2][j] && cc < len - 1; j ++) pf[i][cc ++] = pf[i - 2][j];
				pf[i][cc] = 0;
				cc = 0;
				int lenx = strlen(sf[i - 2]);
				int leny = strlen(sf[i - 1]);
				for(int j = lenx - 1; j >= 0; j --) sf[i][cc ++] = sf[i - 2][j];
				for(int j = leny - 1; j >= 0 && cc < len - 1; j --) sf[i][cc ++] = sf[i - 1][j];
				reverse(sf[i],sf[i] + cc);
				//cout << cc << endl;
				sf[i][cc] = 0;
			}
			//for(int i = 1; i <= n; i ++) cout << i << " : " << sf[i] << " " << pf[i] << endl;
			printf("%lld\n",ans[n]);
		}
	}
	return 0;
}
