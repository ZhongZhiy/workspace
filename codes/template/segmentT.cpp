//注意左右移方向
//注意分割后边界mid+1
//注意参数意义与使用l和cl
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e5 + 5;
ll tree[MAXN << 2], mark[MAXN << 2], n, m, A[MAXN];  //开4倍空间不会超限

void push_down(int p, int len)  //进一步访问子节点，把标记传递下去
{
    if (len <= 1) return;  //如果是叶子节点，就没有标记的必要，也不用传递，直接结束
    tree[p << 1] += mark[p] * (len - len / 2);  //左节点加上父节点打的标记乘上个数就是左节点的总值
    mark[p << 1] += mark[p];  //左节点标记，继承父节点的标记，一忽儿还要去除父节点的标记
    tree[p << 1 | 1] += mark[p] * (len / 2);  //右节点同样操作
    mark[p << 1 | 1] += mark[p];
    mark[p] = 0;  //清除父节点标记，避免下次重复增加
}

void build(int p = 1, int cl = 1, int cr = n)  //建树，递归，root为1
{
    if (cl == cr) return void(tree[p] = A[cl]);  //到达叶子节点，直接赋予对应值，返回
    int mid = (cl + cr) >> 1;  //二分递归赋值
    build(p << 1, cl, mid);  //左节点赋值
    build(p << 1 | 1, mid + 1, cr);  //右节点赋值
    tree[p] = tree[p << 1] + tree[p << 1 | 1];  //当前节点赋值为左子树和右子树的和
}

ll query(int l, int r, int p = 1, int cl = 1, int cr = n)  //查询，相同的操作
{
    if (cl >= l && cr <= r) return tree[p];  //如果目标范围包含当前范围，那么返回就有这个节点的数
    push_down(p, cr - cl + 1);  //否则就往下传递标记，向下搜索
    ll mid = (cl + cr) >> 1, ans = 0;  //把当前节点范围一分为二
    if (mid >= l) ans += query(l, r, p << 1, cl, mid);  //左子树被包含的情况，访问左子树
    if (mid < r) ans += query(l, r, p << 1 | 1, mid + 1, cr);  //右子树被包含的情况，访问右子树,判断mid 《 r是因为右节点是从mid+1开始的
    return ans;  //最后返回答案
}
void update(int l, int r, int d, int p = 1, int cl = 1, int cr = n)  //修改区间，每个区间添加d
{
    if (cl >= l && cr <= r) {tree[p] += d * (cr - cl + 1), mark[p] += d; return;}  //当前节点被完全包含，就直接标记，加上数值
    push_down(p, cr - cl + 1);  //当前节点没有被完全包含，那么就把标记传递下去，把数也传递到下一级
    int mid = (cl + cr) >> 1;  //一分为二
    if (mid >= l) update(l, r, d, p << 1, cl, mid);  //左子树有交集
    if (mid < r) update(l, r, d, p << 1 | 1, mid + 1, cr);  //右子树有交集
    tree[p] = tree[p << 1] + tree[p << 1 | 1];  //更新当前节点的数值为两子节点的和
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> A[i];
    build();
    while (m--)
    {
        int o, l, r, d;
        cin >> o >> l >> r;
        if (o == 1)
            cin >> d, update(l, r, d);
        else
            cout << query(l, r) << '\n';
    }
    return 0;
}
