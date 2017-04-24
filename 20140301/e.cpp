#include <bits/stdc++.h>
using namespace std;

bool visit[450][13][35];
bool vis[450][13][35];
const int eps = 1700;

int leap(int y)
{
	return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

int year[2][13] = {0,31,28,31,30,31,30,31,31,30,31,30,31,
	               0,31,29,31,30,31,30,31,31,30,31,30,31};

void cal(int n,bool flag[450][13][35])
{
while(n --) {
	char s[15];
	scanf("%s",s);
	int y,m,d;
	y = m = d = 0;
	for(int i = 0; i < 4; i ++) y = 10 * y + (s[i] - '0');
	for(int i = 4; i < 6; i ++) m = 10 * m + (s[i] - '0');
	for(int i = 6; i < 8; i ++) d = 10 * d + (s[i] - '0');
	int yy,mm,dd;
	scanf("%s",s);
	yy = mm = dd = 0;
	for(int i = 0; i < 4; i ++) yy = 10 * yy + (s[i] - '0');
	for(int i = 4; i < 6; i ++) mm = 10 * mm + (s[i] - '0');
	for(int i = 6; i < 8; i ++) dd = 10 * dd + (s[i] - '0');
	while(1) {
		flag[y - eps][m][d] = true;
		int lp = leap(y);
		if(y == yy && m == mm && d == dd) break;
		d ++;
		if(d > year[lp][m]) {
			d = 1,m ++;
			if(m > 12) {
				m = 1,y ++;
			}
		}
	}
}
}

int main()
{
	int n,m;
	int cas = 0;
	while(scanf("%d%d",&n,&m) != EOF) {
		if(!n && !m) break;
		memset(visit,0,sizeof(visit));
		memset(vis,0,sizeof(vis));
		cal(n,visit);
		cal(m,vis);
		if(cas) printf("\n");
		printf("Case %d:\n",++ cas);
		bool change = false;
		int y = 1700,mt = 1,date = 1;
		while(y <= 2100) {
			while(!vis[y - eps][mt][date] || visit[y - eps][mt][date]) {
				int flag = leap(y);
				date ++;
				if(date > year[flag][mt]) {
					mt ++;
					date = 1;
					if(mt > 12) {
						mt = 1,y ++;
					}
				}
				if(y > 2100) break;
			}
			if(y > 2100) break;
			int tmp_y = y,tmp_mt = mt,tmp_date = date;
			int now_y = y,now_mt = mt,now_date = date;
			while(vis[y - eps][mt][date] && !visit[y - eps][mt][date]) {
				now_y = y,now_mt = mt,now_date = date;
				int flag = leap(y);
				date ++;
				if(date > year[flag][mt]) {
					mt ++;
					date = 1;
					if(mt > 12) {
						mt = 1,y ++;
					}
				}
				if(y > 2100) break;
			}
			change = true;
			if(tmp_y == now_y && tmp_mt == now_mt && tmp_date == now_date)
				printf("    %d/%d/%d\n",tmp_mt,tmp_date,tmp_y);
			else 
			printf("    %d/%d/%d to %d/%d/%d\n",tmp_mt,tmp_date,tmp_y,now_mt,now_date,now_y);
		}
		if(!change) printf("    No additional quotes are required.\n");
	}
	return 0;
}
