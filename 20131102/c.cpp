#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 200010;
int wa[N],wb[N],wv[N],wss[N];
int cmp(int *r,int a,int b,int len)
{
	return r[a] == r[b] && r[a + len] == r[b + len];
}

void da(int *r,int *sa,int n,int m)
{
	int i,j,p,*x = wa,*y = wb,*t;
	for(i = 0; i < m; i ++) wss[i] = 0;
	for(i = 0; i < n; i ++) wss[x[i] = r[i]] ++;
	for(i = 1; i < m; i ++) wss[i] += wss[i - 1];
	for(i = n - 1; i >= 0; i --) sa[-- wss[x[i]]] = i;
	for(j = 1,p = 1; p < n; j *= 2,m = p) {
		for(p = 0,i = n - j; i < n; i ++) y[p ++] = i;
		for(i = 0; i < n; i ++) if(sa[i] >= j) y[p ++] = sa[i] - j;
		for(i = 0; i < n; i ++) wv[i] = x[y[i]];
		for(i = 0; i < m; i ++) wss[i] = 0;
		for(i = 0; i < n; i ++) wss[wv[i]] ++;
		for(i = 1; i < m; i ++) wss[i] += wss[i - 1];
		for(i = n - 1; i >= 0; i --) sa[-- wss[wv[i]]] = y[i];
		for(t = x,x = y,y = t,p = 1,x[sa[0]] = 0, i = 1; i < n; i ++)
			x[sa[i]] = cmp(y,sa[i - 1],sa[i],j) ? p - 1 : p ++;
	}
}

int rak[N],height[N];
void calheight(int *r,int *sa,int n)
{
	int i,j,k = 0;
	for(i = 0; i < n; i ++) rak[sa[i]] = i;
	for(i = 0; i < n; height[rak[i ++]] = k)
		for(k ? k -- : 0,j = sa[rak[i] - 1]; r[i + k] == r[j + k]; k ++);
}

int r[N],sa[N];
char s[1010][110];
int id[N];
int map[1010][110];

int init(int n)
{
	memset(r,0,sizeof(r));
	memset(sa,0,sizeof(sa));
	memset(rak,0,sizeof(rak));
	memset(height,0,sizeof(height));
	memset(id,-1,sizeof(id));
	int len = 0;
	for(int i = 0; i < n; i ++) {
		for(int j = 0; s[i][j]; j ++) {
			r[len] = s[i][j];
			map[i][j] = len;
			id[len ++] = i;
		}
		r[len ++] = 256 + i;
	}
	return len;
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i ++)
		scanf("%s",s[i]);
	int len = init(n);
//	for(int i = 0; i < len + 1; i ++)
//		cout << r[i] << " ";
//	cout << endl;
	da(r,sa,len + 1,10010);
//	cout << "omg" << endl;
	calheight(r,sa,len);
//	cout << "omg " << len << endl;
//	for(int i = 0; i < len; i ++)
//		cout << sa[i] << " ";
//	cout << endl;
	for(int i = 0; i < n; i ++) {
		int pos = 0,plen = strlen(s[i]),m = strlen(s[i]);
		for(int j = 0; j < m; j ++) {
			int ht = -1,htt;
			bool flag = false;
			for(int k = rak[map[i][j]] + 1; k <= len; k ++) {
				if(height[k] == 0) break;
				if(id[sa[k]] != i) {
					if(ht == -1) ht = height[k];
					else ht = min(ht,height[k]);
					flag = true;
					break;
				}
				if(ht == -1) ht = height[k];
				else ht = min(ht,height[k]);
			}
			htt = ht;
			if(flag == false) htt = -1;
			flag = false;
			ht = -1;
			for(int k = rak[map[i][j]]; k >= 1; k --) {
				if(height[k] == 0) break;
				if(id[sa[k - 1]] != i) {
					if(ht == -1) ht = height[k];
					else ht = min(ht,height[k]);
					flag = true;
					break;
				}
				if(ht == -1) ht = height[k];
				else ht = min(ht,height[k]);
			}
			if(flag == false) ht = -1;
			ht = max(ht,htt);
			if(ht == -1) {
				pos = j;
				plen = 1;
				break;
			}
			else {
				if(j + ht + 1 > m) continue;
				if(ht + 1 < plen) {
					plen = ht + 1;
					pos = j;
				}
			}
		}
		for(int j = 0; j < plen; j ++)
			printf("%c",s[i][pos + j]);
		printf("\n");
	}
	return 0;
}

