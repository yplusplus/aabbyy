#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

char s[3000010];
int a[10010],c[10];

void get(int x,int y)
{
	int n = 0;
	for(int i = x; i <= y; i ++)
		n = 2 * n + c[i];
	if(n < 10) printf("%d",n);
	else printf("%c",'A' + n - 10);
}

void output(int n)
{
	if(n == 0) {
		printf("00");
		return;
	}
//	cout << n << endl;
	int bit = 0;
	while(n) {
		a[++ bit] = n & 1;
		n >>= 1;
	}
	for(int i = 1; i <= bit; i += 7) {
		if(i + 6 >= bit) {
			memset(c,0,sizeof(c));
			c[0] = 0;
			int tmp = bit - i + 1;
			int j = 7;
			while(tmp --) {
				c[j --] = a[i ++];
			}
			get(0,3);
			get(4,7);
			break;
		}
		else {
			c[0] = 1;
			for(int j = 1; j <= 7; j ++)
				c[j] = a[i + 7 - j];
			get(0,3);
			get(4,7);
		}
	}
}

			

int main()
{
	int t;
	gets(s);
	sscanf(s,"%d",&t);
	while(t --) {
		gets(s);
		int len =strlen(s);
		output(len);
		for(int i = 0; s[i] ; i ++) {
			int tmp = s[i];
			int n = tmp / 16,m = tmp % 16;
			if(n < 10) printf("%d",n);
			else printf("%c",'A' + n - 10);
			if(m < 10) printf("%d",m);
			else printf("%c",'A' + m - 10);
		}
		printf("\n");
	}
	return 0;
}

//154 = 128 + 16 + 8 + 2
//    = 10011010

