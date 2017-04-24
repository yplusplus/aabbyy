#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char s[10][10] = {"063","010","093","079","106","103","119","011","127","107"};

int get(char *str)
{
	for(int i = 0; i < 10; i ++)
		if(strcmp(s[i],str) == 0) return i;
	//cout << "fuck" << endl;
}

void output(int n)
{
	int a[15],ct = 0;
	while(n) {
		a[ct ++] = n % 10;
		n /= 10;
	}
	for(int i = ct - 1; i >= 0; i --)
		printf("%s",s[a[i]]);
	cout << endl;
}

int main()
{
	char ss[100010],str[100010];
	while(scanf("%s",str) != EOF) {
		if(str[0] == 'B') break;
		int i = 0,a = 0,b = 0;
		for(i = 0;; i += 3) {
			if(str[i] == '+') break;
			int ct = 0;
			for(int j = 0; j <3; j ++)
				ss[ct ++] = str[i + j];
			ss[ct] = 0;
			a = 10 * a + get(ss);
		}
		i ++;
		for(i; ; i += 3) {
			if(str[i] == '=') break;
			int ct = 0;
			for(int j = 0; j < 3; j ++)
				ss[ct ++] = str[i + j];
			ss[ct] = 0;
			b = 10 * b + get(ss);
		}
		//cout << a << " " << b << " " << str << endl;
		printf("%s",str);
		output(a + b);
	}
	return 0;
}