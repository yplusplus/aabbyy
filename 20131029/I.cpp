#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
struct bignum
{
	int a[N];
	bignum () {
		memset(a,0,sizeof(a));
	}

	void init() {
		memset(a,0,sizeof(a));
	}

	void sub(bignum p) {
		for(int i = 0; i < N; i ++)
			a[i] -= p.a[i];
		for(int i = 0; i < N - 1; i ++) {
			if(a[i] < 0) {
				a[i] += 2;
				a[i + 1] --;
			}
		}
	}

	bool check() {
		for(int i = 0; i < N; i ++)
			if(a[i] < 0) return true;
		for(int i = 0; i < N; i ++)
			if(a[i]) return false;
		return true;
	}

	void output() {
		for(int i = N - 1;i >= 0; i --)
			if(a[i]) {
				for(int j = i; j >= 0; j --)
					printf("%d",a[i]);
				printf("\n");
				return;
			}
	}
}T,TT;

char s[N];
bignum a;

int solve()
{
	int pos = N - 1;
	for(pos; pos >= 0; pos --)
		if(T.a[pos]) break;
	if(pos < 4) return 1;
	if(pos == 4) {
		for(int j = 0; j < 4; j ++) {
			if(T.a[j]) return 2;
		}
		return 1;
	}
	for(int i = pos - 1; i >= 0; i --) {
		if(!T.a[i]) {
			if(i >= 4) return pos - 3;
			else if(i < 3) return pos - 2;
			else if(i == 3) {
				for(int j = 0; j < 3; j ++) {
					if(T.a[j]) return pos - 2;
				}
				return pos - 3;
			}
		}
	}
}

int main()
{
while(scanf("%s",s) != EOF) {
	int n = strlen(s);
	T.init();
	for(int i = 0; i < n; i ++) T.a[i] = s[n - i - 1] - '0';
	int tot = 0;
	a.init();
	a.a[0] = 1;
	T.sub(a);
	if(T.check()) {
		printf("1\n");
		continue;
	}
	T.sub(a);
	if(T.check()) {
		printf("2\n");
		continue;
	}
	a.init();
	a.a[2] = 1;
	T.sub(a);
	if(T.check()) {
		printf("5\n");
		continue;
	}
	T.sub(a);
	if(T.check()) {
		printf("7\n");
		continue;
	}
	T.sub(a);
	if(T.check()) {
		printf("9\n");
		continue;
	}
	T.sub(a);
	if(T.check()) {
		printf("10\n");
		continue;
	}
	T.sub(a);
	if(T.check()) {
		printf("11\n");
		continue;
	}
	//T.output();
	int ans = solve();
//	cout << ans << endl;
	printf("%d\n",3 * (ans - 1) + 13);
}
	return 0;
}