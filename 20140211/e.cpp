#include <bits/stdc++.h>
using namespace std;

bool check(int a[])
{
	int b[15],c[15];
	for(int pair = 0; pair < 9; pair ++) {
		if(a[pair] < 2) continue;
		for(int j = 0; j < 9; j ++) {
			b[j] = a[j];
		}
		b[pair] -= 2;
		for(int j = 0; j < (1 << 9); j ++) {
			int tot = 0;
			bool flag = true;
			for(int k = 0; k < 9; k ++) {
				c[k] = b[k];
				if(j & (1 << k)) {
					if(c[k] < 3) {
						flag = false;
						break;
					}
					c[k] -= 3;
					tot ++;
				}
			}
			if(!flag) continue;
			for(int k = 0; k + 2 < 9; k ++) {
				if(c[k]) {
					int mx = c[k];
					mx = min(c[k + 1],mx);
					mx = min(c[k + 2],mx);
					if(mx < c[k]) {
						flag = false;
						break;
					}
					tot += mx;
					c[k] -= mx,c[k + 1] -= mx,c[k + 2] -= mx;
				}
			}
			if(flag && tot == 4) return true;
		}
	}
	return false;
}

int main()
{
	int a[15],b[15];
	int x;
	while(scanf("%d",&x) != EOF) {
		memset(a,0,sizeof(a));
		x --;
		a[x] ++;
		for(int i = 0; i < 12; i ++) {
			scanf("%d",&x);
			x --;
			a[x] ++;
		}
		bool flag = false;
		for(int i = 0; i < 9; i ++) {
			memcpy(b,a,sizeof(a));
			if(a[i] == 4) continue;
			b[i] ++;
			if(check(b)) {
				if(flag) printf( " ");
				printf("%d",i + 1);
				flag = true;
				//break;
			}
		}
		printf("\n");
	}
	return 0;
}
