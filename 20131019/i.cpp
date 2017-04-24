#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
const int key1 = 131;
const int key2 = 31;
const int mod1 = 12321;
const int mod2 = 1000000007;
int a[N],b[N];
char s[N];

int lowbit(int x)
{
	return x & (-x);
}

void add(int &x,int y,int mod)
{
	x += y;
	x %= mod;
	if(x < 0) x += mod;
}

void insert(int a[],int x,int y,int mod)
{
	for(int i = x; i < N; i += lowbit(i)) {
		add(a[i],y,mod);
	}
}

int query(int a[],int x,int mod)
{
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		add(ans,a[i],mod);
	return ans;
}

int f[2][N];
int ff[2][N];
int main()
{
	scanf("%s",s + 1);
	int n = strlen(s + 1);
	a[0] = b[0] = 1;
	for(int i = 1; i < N; i ++) {
		a[i] = a[i - 1] * 1LL * key1 % mod1;
		b[i] = b[i - 1] * 1LL * key2 % mod2;
	}
	memset(ff,0,sizeof(ff));
	memset(f,0,sizeof(f));
	for(int i = 1; i <= n; i ++) {
		int val = s[i] - 'a' + 1;
		insert(f[0],i,val * 1LL * a[i] % mod1,mod1);
		insert(f[1],i,val * 1LL * a[n - i + 1] % mod1,mod1);
		insert(ff[0],i,val * 1LL * b[i] % mod2,mod2);
		insert(ff[1],i,val * 1LL * b[n - i + 1] % mod2,mod2);
	}
	char cd[25];
	int m,x,y;
	scanf("%d",&m);
	while(m --) {
		scanf("%s",cd);
		if(cd[0] == 'p') {
			scanf("%d%d",&x,&y);
			int val1 = query(f[0],y,mod1) - query(f[0],x - 1,mod1);
			int val2 = query(f[1],y,mod1) - query(f[1],x - 1,mod1);
			//cout << val1 << " " << val2 << endl;
			val1 = 1LL * val1 * a[n - y] % mod1;
			if(val1 < 0) val1 += mod1;
			val2 = 1LL * val2 * a[x - 1] % mod1;
			if(val2 < 0) val2 += mod1;

			int v1 = query(ff[0],y,mod2) - query(ff[0],x - 1,mod2);
			int v2 = query(ff[1],y,mod2) - query(ff[1],x - 1,mod2);
			v1 = 1LL * v1 * b[n - y] % mod2;
			if(v1 < 0) v1 += mod2;
			v2 = 1LL * v2 * b[x - 1] % mod2;
			if(v2 < 0) v2 += mod2;
			if(val1 == val2 && v1 == v2) printf("Yes\n");
			else printf("No\n");
			//cout << val1 << " " << val2 << endl;
		}
		else {
			scanf("%d%s",&x,cd);
			int val = s[x] - 'a' + 1;
			insert(f[0],x,-val * 1LL * a[x] % mod1,mod1);
			insert(f[1],x, -val * 1LL * a[n - x + 1] % mod1,mod1);

			insert(ff[0],x,-val * 1LL * b[x] % mod2,mod2);
			insert(ff[1],x,-val * 1LL * b[n - x + 1] % mod2,mod2);
			s[x] = cd[0];
			val = cd[0] - 'a' + 1;
			insert(f[0],x,val * 1LL * a[x] % mod1,mod1);
			insert(f[1],x,val * 1LL * a[n - x + 1] % mod1,mod1);

			insert(ff[0],x,val * 1LL * b[x] % mod2,mod2);
			insert(ff[1],x,val * 1LL * b[n - x + 1] % mod2,mod2);

		}
	}
	return 0;
}

