#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

const int VSIZE = 6;
const int CSIZE = 20;
char *vowel = "aiyeou";
char *consonant = "bkxznhdcwgpvjqtsrlmf";

int findVowel(char ch) {
    for (int i = 0; i < VSIZE; i++) {
        if (ch == vowel[i]) return i;
    }
    return -1;
}

int findConsonant(char ch) {
    for (int i = 0; i < CSIZE; i++) {
        if (ch == consonant[i]) return i;
    }
    return -1;
}

void solve(string line) {
    for (int i = 0; i < line.length(); i++) {
        if (!isalpha(line[i])) {
            putchar(line[i]);
        } else {
            char ch = line[i];
            ch = tolower(ch);
            int pos = findVowel(ch);
            if (pos != -1) {
                ch = vowel[(pos + 3) % VSIZE];
            } else {
                pos = findConsonant(ch);
                ch = consonant[(pos + 10) % CSIZE];
            }
            if (isupper(line[i])) ch = toupper(ch);
            putchar(ch);
        }
    }
    puts("");
}

int  main() {
    string line;
    while (getline(cin, line)) {
        solve(line);
    }
    return 0;
}
