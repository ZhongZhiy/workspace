#include <bits/stdc++.h>
using namespace std;
#define mx 2000010
#define int long long
#define jiabeiaixc  ios:: sync_with_stdio(false),cin.tie(0), cout.tie(0);
int n, m,k;
string s;
bool is(int x){

}
int a[mx];
void solve(){
    int i,j;
   cin>>n;
    cin>>s;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num[4];
    for(i = 1;i <= 3;i++)num[i] = 0;
    if(n % 2 == 1){
        cout<<-1;
        return;
    }
    int cnt = 0;
    for(i = 0;i < s.size();i+= 3){
        string scnt;

        scnt= s.substr(i,3);
        if(scnt == "COW"){
            a[++cnt] = 1;
            num[1]++;
        }else if(scnt == "OWC"){
                a[++cnt] = 2;
                num[2]++;
        }else{
            a[++cnt] = 3;
            num[3]++;
        }
    }
 int bian = 0;
 int yi = 1;
 for(i = 1;i <= n / 2;i++){
        if(a[i] != a[i + n / 2]){
            yi = 0;
            break;
        }
}

if(yi == 1){
        cout<<1<<endl;
    for(i = 0;i < s.size();i++){
        cout<<1;
        if(i != s.size() - 1)cout<<" ";
    }
    return;
}

int er = 1;

sort(num + 1,num + 4);
    int x1 = num[2];
    int x2 = num[3];
if(num[1] != 0 &&num[2] != 0 && num[3] != 0){
    er = 0;
}else{
    if(x1 % 2 != 0 && x2 % 2 != 0){
        er = 0;
    }
}

    if(er == 1){
            int cx = 0;
            cout<<2<<endl;
        for(i = 1;i <= n;i++){
             if(a[i] == 1){
                cx = 1;
                break;
             }
        }
        if(cx == 1){
            for(i = 1;i <= n;i++){
                if(a[i] == 1){
                    cout<<1<<" "<<1<<" "<<1;
                }else{
                 cout<<2<<" "<<2<<" "<<2;
                }
                if(i != n)cout<<" ";
            }
        }else{
             for(i = 1;i <= n;i++){
                if(a[i] == 2){
                    cout<<1<<" "<<1<<" "<<1;
                }else{
                 cout<<2<<" "<<2<<" "<<2;
                }
            }
              if(i != n)cout<<" ";
        }
        return;
    }
    cout<<3<<endl;
    for(i = 0;i  < s.size();i++){
        if(s[i] == 'C')cout<<1;
        else if(s[i] == 'O')cout<<2;
        else cout<<3;
        if(i != s.size() - 1)cout<<" ";
    }

}
signed main(){
    jiabeiaixc;
    int i,j;
    int t;
    cin>>t>>m;
    for(i = 1;i <= t;i++){
        solve();
        cout<<endl;
    }


    return 0;

}
