
## L1-002 打印沙漏

知识点：循环

解题思路：

1. 首先确定打印的沙漏形状，空个和*与层数的关系
- 沙漏可以分成上下两个部分分别打印
- 上部分是

2. 构造答案数组：
   - 预处理数组 s[i] 表示 i-2 位及以下能表示的最大数
   - 递归函数 sol(v,op,k) 处理数值 v，正负性 op，当前位 k
   - 当 k<2 时为边界情况，根据数值大小和正负性直接构造结果

3. 递归构造过程：
   - 如果当前值 v 大于 s[k-2]（低位能表示的最大值），则当前位必须是 1
   - 当前位取 1 后，如果 v≥2^k，则减去 2^k 继续构造
   - 否则需要用 2^k-v 构造，并且改变符号（op异或1）
   - 继续递归处理更低位

4. 特殊情况处理：
   - 0要单独输出
   - 负数取绝对值后按正数处理，但起始位要调整

复杂度 $O(\log n)$，主要来自于

参考代码：
```C++
#include<bits/stdc++.h>
using namespace std;
#define LL long long
int const N=1e5+10; 
int a[N];
LL s[N];
LL ans,n,k;
void sol(LL v,int op,int k){
    if(k<0||(!v)) return;
    if(k<2){
        if(op==1){
            a[0]=1;
            return;
        } 
        else{
            if(v==1) a[1]=a[0]=1;
            if(v==2) a[1]=1;
            return;
        }
        return;
    }
    if(v>s[k-2]){
        a[k]=1;
        if(v>=(1ll<<k)){
            sol(v-(1ll<<k),op,k-2);
        }
        else{
            sol((1ll<<k)-v,op^1,k-1);
        }    
    }
    else{
        sol(v,op,k-2);    
    }
}
int main(){
    scanf("%lld",&n);
    if(n==0){
        cout<<"0"<<endl;
        return 0;
    }
    if(n>=0) k=-2;
    else k=-1;
    LL sum=0;
    for(;sum<abs(n);){
        k+=2;
        sum+=(1ll<<k);
    }
    s[0]=1; s[1]=2;
    for(int i=2;i<=k;i++){
        s[i]=s[i-2]+(1ll<<i);
    }
    sol(abs(n),(n>0),k);
    for(int i=k;i>=0;i--) printf("%d",a[i]);
}
```

