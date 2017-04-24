#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char s[][110] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.",
"---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

char str[][110] = {"..--","---.",".-.-","----"};

int main()
{
	int len[1111];
	char ss[1010];
	while(scanf("%s",ss) != EOF) {
		string des;
		for(int i = 0; ss[i]; i ++) {
			if(ss[i] >= 'A' && ss[i] <= 'Z') {
				des += s[ss[i] - 'A'];
				len[i] = strlen(s[ss[i] - 'A']);
			}
			else if(ss[i] == '_') len[i] = strlen(str[0]),des += str[0];
			else if(ss[i] == '.') len[i] = strlen(str[1]),des += str[1];
			else if(ss[i] == ',') len[i] = strlen(str[2]),des += str[2];
			else des += str[3],len[i] = strlen(str[3]);
		}
		//cout << des << endl;
		reverse(len,len + strlen(ss));
		int n = strlen(ss);
		for(int i = 0,j = 0; i < n; i ++) {
			char sss[10];
			for(int k = 0; k < len[i]; k ++) sss[k] = des[j + k];
			j += len[i];
			sss[len[i]] = 0;
			for(int k = 0; k < 26; k ++)
				if(!strcmp(s[k],sss)) printf("%c",k + 'A');
			for(int k = 0; k < 4; k ++)
				if(!strcmp(str[k],sss)) {
					if(k ==0) printf("_");
					else if(k == 1) printf(".");
					else if(k == 2) printf(",");
					else printf("?");
				}
		}
		printf("\n");
	}

	return 0;
}
