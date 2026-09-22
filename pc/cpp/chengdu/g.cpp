
#include<bits/stdc++.h>
#include <numeric>
#include <vector>
using namespace std;
#define ll long long
void solve(){
    ll n,m,k;
    cin>>n>>k>>m;
    ll cnt1 = 1, cnt2 = (n / k - 1) / 2, cnt3 = n - n / k;
    if (m > cnt3)
    {
       ll cnt4 = n - m - 1;
       cout << min(n, m + 1 + cnt4 / 2) << '\n';
       return;
    } else {
        cout << cnt1 + cnt2 + m << '\n';
    }

}
int main(){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--)solve();
}
