#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool is_leap(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 != 0 && year % 4 == 0) return true;
    return false;
}

int get_droot(const string &date) {
    for (char ch: date) { if (!isdigit(ch)) return 0; }
    if (date.length() != 8) return 0;

    int dat = stoi(date);
    int day = dat % 100; dat /= 100;
    int month = dat % 100; dat /= 100;
    int year = dat;

    if (year < 1900 || year > 2020) return 0;
    if (month < 1 || month > 12) return 0;
    int days_limit = days[month] + (is_leap(year) && month == 2);
    if (day < 1 || day > days_limit) return 0;

    int r = stoi(date) % 9;
    if (r == 0) r = 9;
    return r;
}

string solve(const string &date, const string &msg) {
    int droot = get_droot(date);
    if (droot == 0) return "none";
    string ans;
    for (char ch: msg) {
        if (ch >= 'a' && ch <= 'z') {
            int x = ch - 'a';
            x += droot;
            x %= 26;
            ans += ('a' + x);
        } else if (ch >= 'A' && ch <= 'Z') {
            int x = ch - 'A';
            x += droot;
            x %= 26;
            ans += ('A' + x);
        } else if (ch == ' ') { 
            ans += '#';
        } else {
            return "none";
        }
    }
    return ans;
}

int main() {
    string date;
    string msg;
    while (getline(cin, date)) {
        getline(cin, msg);
        cout << solve(date, msg) << endl;
    }
    return 0;
}
