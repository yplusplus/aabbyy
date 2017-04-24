#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;

const int N = 3010;
short int dp[N * N / 2];
short int next[N][N];
int sum[N],a[N];
const int mod = 1210009;

struct edge
{
	int v,next;
}e[N * 2];

stack<int> state;
int head[mod + 10],cnt;
void addedge(int u,int v)
{
	state.push(u);
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt ++;
}

int find(int u,int v)
{
	for(int i = head[u]; i != -1; i = e[i].next)
		if(e[i].v == v) return i;
	return -1;
}

int getval(int x)
{
	return ((x << 4) + (x >> 5) + (x ^ 21394)) & ((1 << 20) - 1);
}

void update(short int &x,short int y)
{
	if(x < y) x = y;
}

void init(int n)
{
	sum[0] = 0;
	for(int i = 1; i <= n; i ++)
		sum[i] = sum[i - 1] + (n - i);
	for(int i = 1; i <= n; i ++) {
		int val = getval(a[i]);
		if(find(val,a[i]) == -1) addedge(val,a[i]);
	}
	for(int i = 0; i < cnt; i ++) {
		next[i][n + 1] = -1;
		int val = e[i].v;
		for(int j = n; j >= 1; j --) {
			next[i][j] = next[i][j + 1];
			if(val == a[j]) next[i][j] = j;
		}
	}
}

int getid(int x,int y)
{
	return sum[x - 1] + (y - x);
}

void read(int &x)
{
	char c;
	while(1) {
		c = getchar();
		if(isdigit(c) || c == '-') break;
	}
	int flag = 1;
	if(c == '-') {
		flag = -1;
		x = 0;
	}
	else x = c - '0';
	while(1) {
		c = getchar();
		if(isdigit(c)) {
			x = 10 * x + (c - '0');
		}
		else break;
	}
	x *= flag;
}

stack<int> sta;
int main()
{
	memset(head,-1,sizeof(head));
	int n;
	bool flag = false;
	while(scanf("%d",&n) != EOF) {
		for(int i = 1; i <= n; i ++)
			read(a[i]);
		if(flag) printf("\n");
		flag = true;
		if(n == 1) {
			printf("1\n");
			printf("%d\n",a[1]);
			continue;
		}
		if(n == 2) {
			printf("2\n");
			printf("%d %d\n",a[1],a[2]);
			continue;
		}
		cnt = 0;
		init(n);
		for(int i = 1; i <= n; i ++) 
			for(int j = i + 1; j <= n; j ++) 
				dp[getid(i,j)] = 2;
		int id,val;
		int ans = 0,idx,idy;
		for(int i = 1; i <= n; i ++) {
			for(int j = i + 1; j <= n; j ++) {
				if(ans < dp[getid(i,j)]) {
					ans = dp[getid(i,j)];
					idx = i,idy = j;
				}
				id = getid(i,j);
				val = find(getval(a[i] + a[j]),a[i] + a[j]);
				if(val == -1) continue;
				val = next[val][j + 1];
				if(val == -1) continue;
				update(dp[getid(j,val)],dp[id] + 1);
			}
		}
		while(!sta.empty()) sta.pop();
		sta.push(idy);
		sta.push(idx);
		while(1) {
			bool flag = false;
			for(int i = idx - 1; i >= 1; i --)
				if(a[i] == a[idy] - a[idx] && dp[getid(i,idx)] + 1 == dp[getid(idx,idy)]) {
				   sta.push(i);
				   idy = idx;
				   idx = i;
				   flag = true;
				   break;
				}
			if(!flag) break;
		}
		printf("%d\n",ans);
		while(!sta.empty()) {
			printf("%d",a[sta.top()]);
			sta.pop();
			if(sta.empty()) printf("\n");
			else printf(" ");
		}
		while(!state.empty()) {
			int u = state.top();
			state.pop();
			head[u] = -1;
		}
	}
	return 0;
}

