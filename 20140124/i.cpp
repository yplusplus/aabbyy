#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000010;
int pri[N];
int maxn = 0;
int f[N * 4];
void init()
{
	memset(pri,-1,sizeof(pri));
	for(int i = 2; i < N; i ++)
		if(pri[i] == -1) {
			pri[i] = i;
			if(i > 10000) continue;
			for(int j = i * i; j < N; j += i)
				pri[j] = i;
		}
}

int get_ans(int n)
{
	int ans = 1;
	while(pri[n] != -1) {
		int x = pri[n];
		int cnt = 1;
		while(n % x == 0) n /= x,cnt ++;
		ans *= cnt;
	}
	maxn = max(maxn,ans);
	return ans;
}

struct point
{
	int x,y;
	void read(int id) {
		y = id;
		scanf("%d",&x);
	}
	friend bool operator < (const point &p,const point &q) {
		return p.x < q.x;
	}
}a[100010];
int ans[N];
int main()
{
	init();
	//for(int i = 1; i < N; i ++) get_ans(i);
	//cout << maxn << endl;
	memset(f,0,sizeof(f));
	int n = 1;
	while(scanf("%d",&a[n].x) != EOF) {
		a[n].y = n;
		n ++;
	}
	n --;
	sort(a + 1,a + n + 1);
	int pos = 1;
	for(int i = 1; i < N; i ++) {
		int tot = get_ans(i);
		while(pos <= n && a[pos].x == i) {
			ans[a[pos].y] = f[tot];
			pos ++;
		}
		f[tot] ++;
	}
	for(int i = 1; i <= n; i ++)
		printf("%d\n",ans[i]);
	return 0;
}
