#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define i128 __int128

#define DEBUG
#ifdef DEBUG
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#else
#define de(x)
#define de2(x, y)
#endif
#define enld endl
#define endl '\n'
#define fi(x) for(int i = 1; i <= x; ++i)
#define fi0(x) for(int i = 0; i < x; ++i)
#define fj(n) for(int j = 1; j <= n; ++j)
#define caillo ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
// #define int long long


const int N = 1e3 + 10;
vector<int> pref(string& s) {
    int n = s.size();
    vector<int> pi(n);

    for(int i = 1; i < n; ++i) {
        int j = pi[i-1];

        while(j > 0 && s[i] != s[j])
            j = pi[j-1];

        if(s[i] == s[j]) j++;

        pi[i] = j;
    }
    return pi;
}

int cnt = 0;
void find(string &text, string &pattern) {
    vector<int> pi = pref(pattern);
    int n = text.size(), m = pattern.size();
    int j = 0;

    for(int i = 0;i < n; i++) {
        while(j>0 && text[i] != pattern[j])
            j = pi[j-1];

        if(text[i] == pattern[j]) j++;

        if(j == m) {
            cnt++;
            j = pi[j-1];
        }
    }
}

signed main() {
    string text, pattern;
    cin >> text >> pattern;
    find(text, pattern);
    cout << cnt << endl;

}
