#include <bits/stdc++.h>
using namespace std;

struct Map
{
	vector<string> mp;
	int n,m,id;
	void read() {
		cin >> n >> m;
		mp.clear();
		char tmp[10010];
		for(int i = 0; i < n; i ++) {
			while(1) {
				gets(tmp);
				if(strlen(tmp) > 0) break;
			}
			string temp = "";
			for(int j = 0; j < m; j ++)
				temp = temp + tmp[j];
			mp.push_back(temp);
		}
	}
	void output() {
		n = mp.size();
		m = mp[0].length();
		printf("    MAP %d:\n",id);
		printf("    +");
		for(int i = 0; i < m; i ++) printf("-");
		printf("+\n");
		for(int i = 0; i < n; i ++) {
			printf("    |");
			for(int j = 0; j < m; j ++)
				printf("%c",mp[i][j]);
			printf("|\n");
		}
		printf("    +");
		for(int i = 0; i < m; i ++) printf("-");
		printf("+\n");
	}
}a[110];

bool upp(char c)
{
	return c >= 'A' && c <= 'Z';
}

void match(vector<string> map1,vector<string> map2,int &r,int &c,int &score)
{
	int n1 = map1.size();
	int m1 = map1[0].size();
	int n2 = map2.size();
	int m2 = map2[0].size();
	r = c = score = 0;
	for(int eps_r = -max(n1,n2); eps_r <= max(n1,n2); eps_r ++) 
		for(int eps_c = -max(m1,m2); eps_c <= max(m1,m2); eps_c ++) {
			int sum = 0;
			for(int i = max(0,-eps_r); i < min(n2,n1 - eps_r); i ++)
				for(int j = max(0,-eps_c); j < min(m2,m1 - eps_c); j ++) {
					int x = i + eps_r, y = j + eps_c;
					if(!(x >= 0 && x < n1 && y >= 0 && y < m1)) continue;
					if(upp(map1[x][y]) && upp(map2[i][j]) && map1[x][y] != map2[i][j]) {
						sum = -1000000000;
						break;
					}
					if(upp(map1[x][y]) && upp(map2[i][j])) sum ++;
					//if(eps_r == 0 && eps_c == 4) cout << i << " " << j << " " << x << " " << y << endl;
	
				}
			if(sum > score) {
				score = sum;
				r = eps_r,c = eps_c;
			}
		}
//	cout << n1 << " " << m1 << " " << n2 << " " << m2 << endl;
//	cout << score << " " << r << " " << c << endl;
}

vector<string> get_match(vector<string> map1,vector<string> map2,int r,int c)
{
	int n1 = map1.size(),m1 = map1[0].length();
	int n2 = map2.size(),m2 = map2[0].length();
	int minx = 0,miny = 0,mx = n1 - 1,my = m1 - 1;
	for(int i = 0; i < n2; i ++)
		for(int j = 0; j < m2; j ++) {
			minx = min(minx,i + r);
			miny = min(miny,j + c);
			mx = max(mx,i + r);
			my = max(my,j + c);
		}
	vector<string> ans;
	ans.clear();
	int n = mx - minx + 1,m = my - miny + 1;
	for(int i = 0; i < n; i ++) {
		string tmp;
		for(int j = 0; j < m; j ++)
			tmp = tmp + " ";
		ans.push_back(tmp);
	}
	for(int i = 0; i < n2; i ++) {
		for(int j = 0; j < m2; j ++) {
			int x = i + r,y = j + c;
			ans[x - minx][y - miny] = map2[i][j];
		}
	}
	for(int i = 0; i < n1; i ++) {
		for(int j = 0; j < m1; j ++) {
			if(ans[i - minx][j - miny] == ' ' || upp(map1[i][j])) ans[i - minx][j - miny] = map1[i][j];
		}
	}
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			if(ans[i][j] == ' ') ans[i][j] = '-';
	return ans;
}

int main()
{
	int n;
	int cas = 0;
	while(scanf("%d",&n) != EOF) {
		if(!n) break;
		if(cas) printf("\n");
		for(int i = 1; i <= n; i ++) {
			a[i].read();
			a[i].id = i;
		}
		printf("Case %d\n",++ cas);
		int id = ++ n;
		bool visit[25];
		memset(visit,true,sizeof(visit));
		while(1) {
			bool change = false;
			int ansx = -1,ansy = -1;
			int r,c,score = 0;
			for(int i = 1; i < id; i ++) {
				for(int j = i + 1; j < id; j ++) {
					if(visit[i] == false || visit[j] == false) continue;
					int tmp_r,tmp_c,tmp_score;
					match(a[i].mp,a[j].mp,tmp_r,tmp_c,tmp_score);
					if(tmp_score == 0) continue;
					change = true;
					if(tmp_score > score) {
						score = tmp_score;
						r = tmp_r,c = tmp_c;
						ansx = i,ansy = j;
					}
				}
			}
			if(!change) break;
			a[id ++].mp = get_match(a[ansx].mp,a[ansy].mp,r,c);
			a[id - 1].id = id - 1;
			visit[ansx] = visit[ansy] = false;
		}
		bool flag = false;
		for(int i = 1; i < id; i ++)
			if(visit[i]) {
				if(flag) printf("\n");
				a[i].output();
				flag = true;
			}

	}
	return 0;
}
