

#include<bits/stdc++.h>
#include <numeric>
#include <vector>
using namespace std;
#define ll long long
class mat{
    public:
        int n;
    vector<vector<ll>>s;
    mat(int nn){
        n=nn;
        s.assign(70,vector<ll>(70,0));
    }
    mat operator *(const mat&oth)
    {
        mat ans(n);
        for(int i=0;i<(1<<n);i++)
            for(int j=0;j<(1<<n);j++)
                ans.s[i][j]=-1e6;
        for(int i=0;i<(1<<n);i++)
        {
            for(int j=0;j<(1<<n);j++)
            {
                for(int k=0;k<(1<<n);k++)
                {
                    ans.s[i][j]=max(ans.s[i][j],s[i][k]+oth.s[k][j]);
                }
            }
        }
        return std::move(ans);
    }
};
void solve(){
    ll n,m,k,r;
    cin>>n>>m>>k>>r;
    vector<int>v(n+5,0);
    vector<int>c(n+5,0);
    for(int i=0;i<n;i++)
    {
        cin>>v[i]>>c[i];
    }
    mat matr(n);
    for(int i=0;i<(1<<n);i++)
    {
        for(int j=0;j<(1<<n);j++)
        {
        matr.s[i][j]=0;
        ll cost_tol=0;
        ll v_tol=0;
            for(int pos=0;pos<n;pos++)
            {
                int flag1=(i>>pos)&1;
                int flag2=(j>>pos)&1;
                if(flag1)
                {
                    if(flag2) cost_tol+=c[pos]+k;
                    else cost_tol+=c[pos];
                    v_tol+=v[pos];
                }
            }
            if(cost_tol<=m) matr.s[i][j]=v_tol;
            else matr.s[i][j]=-1e6;
        }
    }
    auto qp=[&](mat x,ll k)
    {
        mat res(n);
        int ok = 0;
        while(k)
        {
            if(k&1) {
                if (ok)
                    res=res*x;
                else
                    res = x, ok = 1;
            }
            x=x*x;
            k>>=1;
        }
        return std::move(res);
    };
    auto res=qp(matr,r);
    ll ans=0;
    for(int i=0;i<(1<<n);i++)
    {
        for(int j=0;j<(1<<n);j++)
            ans=max(ans,res.s[i][j]);
            // cout<<res.s[i][j]<<' ';
    }
    cout<<ans<<'\n';

}
int main(){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--)solve();
}
/*
    3
    3 7 1 1
    59 3
    13 2
    81 4
    5 14 2 1
    66 8
    20 2
    25 4
    39 6
    57 7
    4 13 7 1
    18 2
    13 5
    33 4
    7 1
 */
