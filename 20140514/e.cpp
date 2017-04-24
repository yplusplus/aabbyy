#include <bits/stdc++.h>
using namespace std;

const int N = 510;
char s[N][N];
bool visit[N][N];
vector<int> a[N];
char buffer[1 << 15];
int pos[N];
bool f[N][N];
int ans[N];
int n,tot,re[N],cc,m;
bool flag;
bool vv[N];
int vis[N];
int times = 0;
int lt[N];

bool check()
{
	int cnt = 0;
	queue<int> q;
	q.push(re[cc]);
	vis[re[cc]] = ++ times;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = 1; i <= n; i ++)
			if(vis[i] != times && !vv[i]) {
				vis[i] = times;
				cnt ++;
				q.push(i);
			}
	}
	return cnt == n - cc;
}

void dfs()
{
	if(cc == n - 1) {
		if(visit[re[cc]][n]) {
	//		cout << n << endl;
	//		for(int i = 1; i <= n; i ++) cout << re[i] << " ";
	//		cout << endl;
			for(int i = 1; i <= n; i ++) ans[i] = re[i];
			ans[n] = n;
			flag = true;
		}
		return;
	}
	if(flag) return;
	//if(!check()) return;
	for(int i = 1; i <= m && !flag; i ++) {
		if(pos[i] < a[i].size() - 1 && visit[re[cc]][a[i][pos[i]]]) {
			re[++ cc] = a[i][pos[i] ++];
			lt[re[cc]] = pos[i];
			dfs();
			pos[i] --;
			cc --;
		}
		if(pos[i] == a[i].size() - 1) continue;
		if(cc == 1) continue;
		for(int j = lt[a[i][pos[i] - 1]]; j < cc && !flag; j ++) {
			if(visit[re[j]][a[i][pos[i]]] && visit[a[i][pos[i]]][re[j + 1]]) {
			   for(int k = cc; k > j; k --) {
				   re[k + 1] = re[k];
			   }
			   re[j + 1] = a[i][pos[i] ++];
			   cc ++;
			   for(int k = j + 1; k <= cc; k ++) lt[re[k]] = k;
			   dfs();
			   pos[i] --;
			   for(int k = j + 1; k < cc; k ++) {
				   re[k] = re[k + 1];
				   lt[re[k]] = k;
			   }
			   cc --;
			}	   
		}
	}	
		
}

int main()
{
	freopen("inspection.in","r",stdin);
	freopen("inspection.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i ++) {
		scanf("%s",s[i] + 1);
		for(int j = 1; j <= n; j ++) {
			if(s[i][j] == '-') visit[i][j] = true;
		}
	}
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= n; j ++)
			f[i][j] = visit[i][j];
		f[i][i] = true;
	}
	for(int k = 1; k <= n; k ++)
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				f[i][j] |= (f[i][k] & f[k][j]);
	gets(buffer);
	for(int i = 1; i <= m; i ++) {
		gets(buffer);
		stringstream strin(buffer);
		int x;
		while (strin >> x) {
			a[i].push_back(x);
		}
	}
	for(int i = 1; i <= m; i ++)
		for(int j = 1; j < a[i].size(); j ++)
			if(!f[a[i][j - 1]][a[i][j]]) {
	//			cout << a[i][j - 1] << " " << a[i][j] << endl;
				puts("-1");
				return 0;
			}
	flag = false;
	for(int i = 1; i <= m; i ++) pos[i] = 1;
	re[++ cc] = 1;
	lt[1] = 1;
	dfs();
	if(!flag) {
		puts("-1");
		return 0;
	}
	for(int i = 1; i <= n; i ++) cout << ans[i] << " ";
	cout << endl;
	return 0;
}
