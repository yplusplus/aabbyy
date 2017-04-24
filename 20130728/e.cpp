#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a = 0,b = 0;
int main()
{
    ios::sync_with_stdio(false);
    char c;
    char s[10055];
    while((c = getchar()) != EOF) {
        if(c >= 'a' && c <= 'z') {
            int ct = 0;
            s[ct ++] = c;
            while((c = getchar()) != EOF) {
                if(c >= 'a' && c <= 'z') s[ct ++] = c;
                else break;
            }
            s[ct] = 0;
            if(!strcmp(s,"tram")) a ++;
            else if(!strcmp(s,"trolleybus")) b ++;
        }
    }
    if(a > b) printf("Tram driver\n");
    else if(a == b) printf("Bus driver\n");
    else printf("Trolleybus driver\n");
    return 0;
}


