#include<bits/stdc++.h>
#include <numeric>
#include <vector>
using namespace std;

void solve(){
    int n, m, k, b; cin >> n >> m >> k >> b;

    int cnt = 0;
    int cnt2 = 0;

    for(int i = 1;i <= n; ++i){
        vector<int> tp(m), ttp(m);


        for(int j = 0;j < m; ++j){
            cin >> tp[j];
            if(tp[j] >= 1) ttp[j] = tp[j]-1;
            else ttp[j] = tp[j] + 1;
        }

        int suma = accumulate(tp.begin(), tp.end(),0LL);
        int sumb = accumulate(ttp.begin(), ttp.end(), 0LL);
        if(suma >= k) cnt++;
        else if(sumb >= k) cnt2++;
    }

    cnt += min(cnt2, b);

    cout << cnt << endl;
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--)solve();
}
