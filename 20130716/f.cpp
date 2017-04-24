#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

const int N = 200010;
#define rep(i,a,b) for(i = a; i <= b; i ++)
int nxt[N],ex[N];

void ex_kmp(char *s,char *str)
{
	int lena = strlen(s);
	int lenb = strlen(str);
	nxt[0] = lenb,nxt[1] = lenb - 1;
	int i,j,k = 1,p,L;
	rep(i,0,lenb - 2) if(str[i] != str[i + 1]) {
		nxt[1] = i;
		break;
	}
	rep(i,2,lenb - 1) {
		p = k + nxt[k] - 1;
		L = nxt[i - k];
		if(i + L <= p) {
			nxt[i] = L;
		}
		else {
			j = p - i + 1;
			if(j < 0) j = 0;
			while(i + j < lenb && str[i + j] == str[j]) j ++;
			nxt[i] = j;
			k = i;
		}
	}
	int minlen = lena >= lenb ? lena : lenb;
	ex[0] = minlen;
	rep(i,0,minlen - 1) if(s[i] != str[i]) {
		ex[0] = i;
		break;
	}
	k = 0;
	rep(i,1,lena - 1) {
		p = k + ex[k] - 1,L = nxt[i - k];
		if(i + L <= p) {
			ex[i] = L;
		}
		else {
			j = p - i + 1;
			if(j < 0) j = 0;
			while(i + j < lena && j < lenb && s[i + j] == str[j]) j ++;
			ex[i] = j;
			k = i;
		}
	}
}

int get_power(char *s,char *str)
{
	int lena = strlen(s),lenb = strlen(str);
	ex_kmp(s,str);
	int ans = 0;
	for(int i = 0; i < lenb; i ++)
		if(ex[i] >= lenb) ans ++;
	return lenb / ans;
}

int cmp(char *s)
{
	int n = strlen(s);
	int i = 0,j = 1,k = 0;
	while(i < n && j < n && k < n) {
		if(s[(i + k) % n] == s[(j + k) % n]) k ++;
		else {
			if(s[(i + k) % n] > s[(j + k) % n]) i += k + 1;
			else j += k + 1;
			if(i == j) j ++;
			k = 0;
		}
	}
	return min(i,j);
}

char tmp[N],s[N],str[N],ss[N];
unsigned long long key1 = 37,key2 = 131;
struct point
{
	unsigned long long x,y;
	point() {}
	point(unsigned long long x,unsigned long long y):x(x),y(y) {}
	friend bool operator < (const point &p,const point &q) {
		if(p.x != q.x) return p.x < q.x;
		return p.y < q.y;
	}
};
set<point> Set;

bool check(int p,int len,int n)
{
	int st = cmp(str);
	for(int i = 0; i < len; i ++)
		s[i] = str[(i + st) % len];
	s[len] = 0;
	strcpy(tmp,s);
	Set.clear();
	for(int i = 0; i < n; i += len) {
		unsigned long long val1 = 0,val2;
		for(int j = 0; j < len; j ++) {
			str[j] = ss[i + j];
			val1 = val1 * key1 + (ss[i + j] - 'a' + 1);
			val2 = val2 * key2 + (ss[i + j] - 'a' + 1);
		      	if(Set.count(point(val1,val2))) return false;
			Set.insert(point(val1,val2));

		}
		str[len] = 0;
		st = cmp(str);
		for(int i = 0; i < len; i ++)
			s[i] = str[(i + st) % len];
		s[len] = 0;
		if(strcmp(s,tmp)) return false;
	}
	return true;
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int cas = 1; cas <= t; cas ++) {
		scanf("%s",ss);
		int n = strlen(ss);
		int len;
		bool flag = 0;
		for(int i = 1; i <= n; i ++) {
			if(n % i) continue;
			if(i * i < n) continue;
			len = i;
			for(int j = 0; j < len; j ++)
				str[j] = s[j] = s[j + len] = ss[j];
			str[len] = 0;
			s[2 * len] = 0;
			int x = get_power(s,str);
			if(1LL * x * i != n) continue;
			if(check(x,i,n)) {
				flag = i;
				break;
			}
		}
		printf("Case #%d: ",cas);
		if(flag) {
			int st = cmp(str);
			for(int i = 0; i < len; i ++)
				s[i] = str[(i + st) % len];
			s[len] = 0;
			printf("%s\n",s);
		}
		else printf("Impossible\n");
	}
	return 0;
}



