#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

const int N = 250010;
int a[N],b[N],nxt[N],c[N],d[N];

void get_next(int m)
{
	int i = 0, j = -1;
	nxt[0] = -1;
	while(i <= m) {
		if(j == -1 || a[i] == a[j]) {
			i ++,j ++;
			nxt[i] = j;
		}
		else j = nxt[j];
	}
}

int get_ans(int pos,int m,int &ans,int &p)
{
	int sum = 0;
	for(int i = 0; i < m; i ++) {
		if(c[m - i - 1] != d[pos - i - 1]) sum ++;
		if(ans != -1 && sum >= ans) break;
	}
	if(ans == -1) ans = sum, p = pos - m + 1;
	else if(sum < ans) {
		ans = sum;
		p = pos - m + 1;
	}
}

void kmp(int n,int m)
{
	int ans = -1;
	int tot = 0;
	int i = 0,j  = 0,pos = -1;
	while(i < n) {
		//cout << i << " " << j << " " << b[i] << " " << a[j] << endl;
		if(j == -1 || b[i] == a[j]) {
			i ++,j ++;
		}
		else j = nxt[j];
		if(j == m) {
			if(tot ++ < 100) {
				get_ans(i,m,ans,pos);
			}
			else if(rand() % 15 == 0) {
				get_ans(i,m,ans,pos);
			}
			j = nxt[j];
		}
		//cout << i << " " << j << endl;
	}
	if(ans == -1) printf("No\n");
	else {
		printf("Yes\n");
		printf("%d %d\n",ans,pos);
	}
}

int getval(char *s) 
{
	int ans = 0;
	for(int i = 0; s[i] ; i ++)
		ans = 2 * ans + (s[i] - '0');
	return ans;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	char s[25];
	for(int i = 0; i < n; i ++) {
		scanf("%s",s);
		int val = getval(s);
		b[i] = val >> 1;
		d[i] = val & 1;
	}
	for(int i = 0; i < m; i ++) {
		scanf("%s",s);
		int val = getval(s);
		a[i] = val >> 1;
		c[i] = val & 1;
	}
	/*
	for(int i = 0; i < n; i ++)
		cout << b[i] << " ";
	cout << endl;
	for(int i = 0; i < m; i ++)
		cout << a[i] << " ";
	cout << endl;
	*/
	a[m] = -1;
	get_next(m);
	kmp(n,m);
	return 0;
}
