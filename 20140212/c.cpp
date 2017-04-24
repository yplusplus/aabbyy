#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
char s[N];

void solve()
{
	bool flag = true;
	int sum = 0;
	int a[N],b[N];
	int n = strlen(s);
	memset(b,0,sizeof(b));
	int m = n - 1,tot = 0;
	while(m >= 0 && s[m] == '0') m --,tot ++;
	for(int i = 0; i < n; i ++) {
		a[i] = s[i] - '0';
		if(a[i] != 9 && i < m) flag = false;
		if(i == 0) b[i] = a[i];
		else b[i] = b[i - 1] + a[i];
		sum += a[i];
	}
	if(flag) {
		printf("1");
		while(tot --) printf("0");
		sum --;
		printf("%d",sum % 9);
		for(int i = 0; i < m; i ++)
			printf("9");
		printf("\n");
		return;
	}
	flag = true;
	for(int i = 0; i < n; i ++) {
		if(flag) {
			if(a[i] == 9) {
				printf("9");
				sum -= 9;
				continue;
			}
			else {
				int sumx = b[m - 1] - b[i];
				int sumy = (m - 1 - i) * 9;
				if(sumx == sumy) {
					printf("%d",a[i] + 1);
					flag = false;
					sum -= (a[i] + 1);
				}
				else {
					printf("%d",a[i]);
					sum -= a[i];
				}
			}

		}
		else {
			int len = (n - i - 1) * 9;
			int x = max(0,sum - len);
			printf("%d",x);
			sum -= x;
		//	if(i == n - 1) printf("\nfuck  %d", sum);
		}
	}
	printf("\n");
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t --) {
		scanf("%s",s);
		solve();
	}
	return 0;
}
