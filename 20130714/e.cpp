#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

char s[1010];
map<string,int> ma;
struct point
{
	char s[110];
	int fre,len;
	friend bool operator < (const point &p,const point &q) {
	       if(p.fre != q.fre) return p.fre > q.fre;
	       if(p.len != q.len) return p.len > q.len;
	       return strcmp(p.s,q.s) < 0;
	}
}a[5010];

bool isletter(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char change(char c)
{
	if(!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z')) return 0;
	if(c >= 'a') return c;
	return c + 32;
}

int main()
{
	int t,n;
	gets(s);
	sscanf(s,"%d",&t);
	while(t --) {
		gets(s);
		sscanf(s,"%d",&n);
		ma.clear();
		while(n --) {
			char c;
			char ss[1010];
			while(1) {
				c = getchar();
				if(c == '\n') break;
				if(!isletter(c)) continue;
				cin.putback(c);
				int cc = 0;
				while(1) {
					c = getchar();
					if(!isletter(c)) break;
					s[cc ++] = c;
				}
				bool flag = false;
				if(c == '\n') flag = true;
				if(!cc) {
					if(flag) break;
					else continue;
				}
				s[cc] = 0;
				int len = 0;
				for(int i = 0; s[i]; i ++) {
					c = change(s[i]);
					if(c) ss[len ++] = c;
				}
				ss[len] = 0;
				if(!len) continue;

				ma[ss] ++;
				if(flag) break;

			}
		}
		if(ma.size() == 0) {
			printf("\n");
			continue;
		}
		int ct = 0;
		for(map<string,int>::iterator it = ma.begin(); it != ma.end(); it ++) {
			a[++ ct].fre = it->second;
			a[ct].len = it->first.length();
			for(int i = 0; i < it->first.length(); i ++)
				a[ct].s[i] = it->first[i];
			a[ct].s[it->first.length()] = 0;
		}
		sort(a + 1,a + ct + 1);
		int i = 1;
		if(a[1].fre == 1) {
			printf("\n");
			continue;
		}
		while(i <= ct) {
			int j = i;
			while(j <= ct && a[j].fre == a[i].fre && a[j].len == a[i].len) j ++;
			if(i + 1 == j) printf("%s",a[i].s);
			else printf("%s",a[j - 2].s);
			while(j <= ct && a[j].fre == a[i].fre) j ++;
			if(j > ct || a[j].fre == 1) {
				printf("\n");
				break;
			}
			else printf(" ");
			i = j;
		}
	}
	return 0;
}
