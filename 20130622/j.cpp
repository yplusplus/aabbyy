#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
char s[N][N];
int ans[N][N];

int dir[4][2] = {0,1,0,-1,1,0,-1,0};

int main()
{
	memset(ans,0,sizeof(ans));
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i ++)
		scanf("%s",s[i] + 1);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(s[i][j] == '.') continue;
			else if(s[i][j] == 'b') {
				printf("NO\n");
				return 0;
			}
			else {
				if(ans[i + 1][j] && ans[i][j + 1]) {
					printf("NO\n");
					return 0;
				}
				if(s[i + 1][j] != 'b' && s[i][j + 1] != 'b') {
					printf("NO\n");
					return 0;
				}
				if(s[i][j + 1] == 'b' && !ans[i][j + 1]) {
					if(s[i][j + 2] != 'w') {
						printf("NO\n");
						return 0;
					}
					if(ans[i][j + 2]) {
						printf("NO\n");
						return 0;
					}
					s[i][j] = '.';
					s[i][j + 1] = '.';
					s[i][j + 2] = '.';
					int visit[15];
					memset(visit,0,sizeof(visit));
					for(int k = j; k <= j + 2; k ++) {
						for(int r = 0; r < 4; r ++) {
							int x = i + dir[r][0];
							int y = k + dir[r][1];
							visit[ans[x][y]] = 1;
						}
					}
					for(int k = 1; k <= 4; k ++) {
						if(!visit[k]) {
							ans[i][j] = k;
							ans[i][j + 1] = k;
							ans[i][j + 2] = k;
							break;
						}
					}
				}
				else if(s[i + 1][j] == 'b' && !ans[i + 1][j]) {
					if(s[i + 2][j] != 'w') {
						printf("NO\n");
						return 0;
					}
					if(ans[i + 2][j]) {
						printf("NO\n");
						return 0;
					}
					s[i][j] = '.';
                    s[i + 1][j] = '.';
                    s[i + 2][j] = '.';
                    int visit[15];
                    memset(visit,0,sizeof(visit));
                    for(int k = i; k <= i + 2; k ++) {
                        for(int r = 0; r < 4; r ++) {
                            int x = k + dir[r][0];
                            int y = j + dir[r][1];
                            visit[ans[x][y]] = 1;
                        }
                    }
                    for(int k = 1; k <= 4; k ++)
                        if(!visit[k]) {
                            ans[i][j] = k;
                            ans[i + 1][j] = k;
                            ans[i + 2][j] = k;
                            break;
                        }
                }
            }
    printf("YES\n");
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= m; j ++) {
            if(!ans[i][j]) printf(".");
            else printf("%c",'a' + ans[i][j] - 1);
        }
        printf("\n");
    }
    return 0;
}




