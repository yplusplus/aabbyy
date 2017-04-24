#include <bits/stdc++.h>
using namespace std;

char s[15][110];

int main()
{
	int t;
	scanf("%d",&t);
	while(t --) {
		for(int i = 0; i < 12; i ++)
			scanf("%s",s[i]);
		int x,y;
		sscanf(s[6],"%d",&x);
		sscanf(s[10],"%d",&y);
		//cout << x << " " << y << endl;
		if(s[3][0] == 'h') {
			int minx = -1,maxx = -1;
			for(int i = 0; i <= 30 && minx == -1; i ++)
				for(int j = 0; j <= 30; j ++)
					if(x + i > y + j) {
						minx = i;
						break;
					}
					else if(x + i == y + j) {
						if(i >= y) {
							minx = i;
							break;
						}
					}
			for(int i = 0; i <= 30; i ++)
				for(int j = 0; j <= 30; j ++)
					if(x + i < y + j) {
						if(maxx == -1 || maxx < i) maxx = i;
					}
					else if(x + i == y + j) {
						if(i <= y) {
							if(maxx == -1 || maxx < i) maxx = i;
						}
					}
			printf("%d %d\n",minx,maxx);
		}
		else {
			int minx = -1,maxx = -1;
			for(int i = 0; i <= 30 && minx == -1; i ++)
				for(int j = 0; j <= 30; j ++)
					if(x + i > y + j) {
						minx = i;
						break;
					}
					else if(x + i == y + j) {
						if(x >= j) {
							minx = i;
							break;
						}
					}
			for(int i = 0; i <= 30; i ++)
				for(int j = 0; j <= 30; j ++)
					if(x + i < y + j) {
						if(maxx == -1 || maxx < i) maxx = i;
					}
					else if(x + i == y + j) {
						if(x <= j) {
							if(maxx == -1 || maxx < i) maxx = i;
						}
					}

			printf("%d %d\n",minx,maxx);
		}
	}
	return 0;
}
