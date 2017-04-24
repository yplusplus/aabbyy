#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
stack<int> stk;
vector<int> v[N];
int ans[N],deg[N];

int main()
{
	int t;
	scanf("%d",&t);
	while(t --) {
		int n,m,x,y;
		memset(deg,0,sizeof(deg));
		while(!stk.empty()) stk.pop();
		for(int i = 0; i < N;i ++) v[i].clear();
		scanf("%d%d",&n,&m);
		while(m --) {
			scanf("%d%d",&x,&y);
			v[x].push_back(y);
			deg[y] ++;
		}
		for(int i = 1; i <= n; i ++)
			if(deg[i] == 0) stk.push(i);
		bool mul = false;
		int tot = 0;
		while(!stk.empty()) {
			if(stk.size() >= 2) mul = true;
			int u = stk.top();
			stk.pop();
			ans[++ tot] = u;
			for(int i = 0; i < v[u].size(); i ++) {
				x = v[u][i];
				deg[x] --;
				if(deg[x] == 0) stk.push(x);
			}
		}
		if(tot < n) printf("recheck hints\n");
		else if(mul) printf("missing hints\n");
		else {
			for(int i = 1; i <= n; i ++) {
				printf("%d",ans[i]);
				if(i == n) printf("\n");
				else printf(" ");
			}
		}
	}
	return 0;
}
