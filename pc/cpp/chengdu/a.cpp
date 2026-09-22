
#include<bits/stdc++.h>
#include <numeric>
#include <vector>
using namespace std;
#define ll long long
void solve(){
    ll n;
    cin>>n;
    vector<int>a(n+5,0);
    vector<int>b(n+5,0);
    vector<vector<int>>adj(n+5);
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
    }
    for(int i=1;i<n;i++)
    {
        ll a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int>siz(n+5,1);
    vector<int>son(n+5,0);
    vector<vector<int>>cnt_zero(n+5,vector<int>(2,0));
    auto cal=[&](auto &&self,int x,int f)->void
    {
        if(a[x]==0) cnt_zero[x][0]++;
        if(b[x]==0) cnt_zero[x][1]++;
        for(auto v:adj[x])
        {
            if(v==f) continue;
            self(self, v,x);
            siz[x]+=siz[v];
            if(siz[v]>siz[son[x]]) son[x]=v;
            cnt_zero[x][0]+=cnt_zero[v][0];
            cnt_zero[x][1]+=cnt_zero[v][1];
        }
    };
    cal(cal,1,0);
    vector<bool>ans(n+5,0);
    auto dfs=[&](auto &&self,int x,int f)->tuple<int,int,unordered_map<int,int>>{
        int cnta=0,cntb=0;
        unordered_map<int,int>mp_now;
        if(a[x]) mp_now[a[x]]++;
        if(b[x]) mp_now[b[x]]--;
        for(auto [key,cnt]:mp_now)
        {
            if(cnt>0) cnta+=cnt;
            else if(cnt<0) cntb+=-cnt;
        }

        for(auto v:adj[x])
        {
            if(v==f )continue;
            auto [cnt_a,cnt_b,mp]=self(self,v,x);
            if(mp_now.size()<mp.size()) swap(mp,mp_now),swap(cnt_a,cnta),swap(cnt_b,cntb);
            for(auto [key,cnt]:mp)
            {
                auto ori=mp_now[key];
                mp_now[key]+=cnt;
                auto now=mp_now[key];
                if(ori>0) cnta-=ori;
                else if(ori<0) cntb-=-ori;
                if(now>0) cnta+=now;
                else if(now<0) cntb+=-now;
            }
        }
        if(cnta<=cnt_zero[x][1]&&cntb<=cnt_zero[x][0]) ans[x]=1;
        // cout<<x<<' '<<cnta<<' '<<cnt_zero[x][0]<<cntb<<'\n';
        return make_tuple(cnta,cntb,std::move(mp_now));
    };
    dfs(dfs,1,0);
    for(int i=1;i<=n;i++) cout<<ans[i];
    cout<<'\n';
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
