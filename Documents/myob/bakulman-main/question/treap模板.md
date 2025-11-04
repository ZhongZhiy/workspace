```cpp

//bst二叉搜索树
//当前节点的左子树中的任何一个点的权值都《 当前节点的权值
//使用中序遍历，是一个从小到到的顺序
//本质就是，动态维护一个有序序列
//
//操作1）插入  2）删除  3）找前驱后继
//
//trap让BST尽量随机
//int key , val ;key 
//左旋和右旋不改变中序遍历的顺序
//
//如果需要处理查询不存在的节点，可以采取两种措施，1）先插入，再查询，再删除， 2）查询函数中，返回1,代表不存在的节点的个数


#include<bits/stdc++.h>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define f(n) for(int i = 0;i < n; ++i)
#define ff(i, a, b) for(int i = a; i < b; ++i)
typedef long long ll;
typedef unsigned long long ull;

const int N = 1e5 + 1000, INF = 1e8;

int n;
//val作为堆的优先级，随机分配，利于堆的稳定性，key是对于二叉搜索树的值，能够一直保持中序情况下有序
struct{
	int l, r;  //l为左子树，r为右子树
	int key, val;  //key为节点的值，val为旋转的时候的优先级
	int cnt, size;  //cnt为节点值相同的个数，size为树所有节点的个数

}tr[N];

int root, idx;  //根节点和节点号

void pushup(int p) {  //用于每次修改，旋转的时候更新树的大小
	tr[p].size = tr[tr[p].r].size + tr[tr[p].l].size + tr[p].cnt;
}

int get_node(int key) {  //新建节点操作
	tr[++ idx].key = key;
	tr[idx].val = rand();  //随机值，保证平衡性
	tr[idx].cnt = tr[idx].size = 1;
	return idx;
}

void build() {
	get_node(-INF), get_node(INF);  //为安全而生的守门员，-INF为跟，INF为叶
	root = 1, tr[1].r = 2;
	pushup(root);  // 每次做出更改需要更新树的大小
}

void zig(int &p) {  //右旋,把左子树旋上去,左子树旋到右边
	int q = tr[p].l;  //左子树用q表示
	tr[p].l = tr[q].r, tr[q].r = p, p = q;  //依次，先把p左子树的右子树挂在p的左子树，然后把p挂在q的右子树，最后更新父子关系，让q成为父节点
	pushup(tr[p].r),pushup(p);  //依次更新新父节点的左子树，和新父节点
}

void zag(int &p) {  //把右子树旋到左边
	int q = tr[p].r;  //左旋，把右子树q旋转上来
	tr[p].r = tr[q].l, tr[q].l = p, p = q;  //依次执行，把q的左子树挂在p的右子树，再把p作为q的左子树
	pushup(tr[p].l), pushup(p);  //依次更新新父节点的右节点，和新父节点
}

void inser(int &p, int key) {  //p是插入的指针位置，刚开始是根节点，之后慢慢移动
	if(!p) p = get_node(key);  //如果是空的，就创建新节点
	else if(tr[p].key == key) {  //如果刚好碰到相同的值了，就当前节点的个数+1, 
		tr[p].cnt++;
	}
	else if(tr[p].key > key) {  //如果这个值小于节点值，那么就插入到节点的左边寻找合适的位置
		inser(tr[p].l, key);
		if(tr[tr[p].l].val > tr[p].val) zig(p);  //因为插入到了左子树，因此考虑比较插入的这个左子树的这个节点的优先级，需不需要右旋一下，恢复堆的稳定
	}
	else if(tr[p].key < key) {
		inser(tr[p].r, key);
		if(tr[tr[p].r].val > tr[p].val) zag(p); //如果插入到右子树，插入的右子树的优先级比父节点高，那么就p的右子树左旋上来
	}
	pushup(p);  //更新节点数值
}

void rm(int &p, int key) {
	if(!p) return;  //如果节点就是空的，直接返回
	if(tr[p].key == key) {  //找到了，继续处理
		if(tr[p].cnt > 1) tr[p].cnt--;  //如果节点个数有多个，就减少一个就是了
		else if(tr[p].l || tr[p].r) {  //如果节点个数只用一个，并且不是子叶，那么就需要继续处理，通过不断旋转让这个节点成为子叶，再删除
			if(!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val) {  //判断旋转方向，如果右节点为空，那么就只能左旋，或者，左节点的优先级高于右节点，那么就右旋，否则左旋
				zig(p);  //右旋
				rm(tr[p].r, key);  //右旋向下移送
			}
			else {
				zag(p);
				rm(tr[p].l, key);
			}
		} 
		else 
			p = 0;  //如果是子叶的话，就直接为零就可以了
	}
	else if(tr[p].key > key) rm(tr[p].l, key);  //如果节点值大于需要删除的值，那么就到左边去删除
	else rm(tr[p].r, key);  //否则到右边删除对应值
	
	pushup(p);  //删除对应值之后对对应值相关数据进行更新
}

int get_rank_by_key(int p, int key) {   // 根据节点值找排位
	if(!p) return 1;  //如果节点不存在，返回1,这样就是这个不存在的节点的位次
	if(tr[p].key == key) return tr[tr[p].l].size + 1;  //找到对应节点，那么对应位置就为左子树的大小+1
	if(tr[p].key > key) return get_rank_by_key(tr[p].l, key);  //如果节点大于寻找的值，那么就往左边找
	return tr[tr[p].l].size + tr[p].cnt + get_rank_by_key(tr[p].r, key);  //如果节点小于寻找的值，那么就往右边找，因为是从根节点开始找的，所以结果要加上在右边的值和这个节点的数量

}

int get_key_by_rank(int p, int rank) {
	if(!p) return INF;  //如果找不到这个排名，就返回无穷大
	if(tr[tr[p].l].size >= rank) return get_key_by_rank(tr[p].l, rank);  //如果左子树的大小大于需要找的排位，那么就往左子树寻找，等于的时候因为所处节点排在rank + 1,所以还是要往左边找
	if(tr[tr[p].l].size + tr[p].cnt >= rank) return tr[p].key;  //如果左子树的大小小于排位的话，那么就可能在p节点或是p的右子树，如果左子树的数量加上p节点的个数比排位大了，那么排位就位于p节点
	return get_key_by_rank(tr[p].r, rank - tr[tr[p].l].size - tr[p].cnt);  // 如果排位在p节点的右子树，那么就减去左子树和p节点的个数进行寻找
}

int get_prev(int p, int key) {
	if(!p) return -INF;  //如果节点不存在就返回负无穷
	if(tr[p].key >= key) return get_prev(tr[p].l, key);  //如果当前节点值大于需要找的节点，那么就找左子树
	return max(tr[p].key, get_prev(tr[p].r, key));  //如果当前节点值小于需要的值，那么就找小于中的最大值，也就是前驱了
}

int get_next(int p, int key) {
	if(!p) return INF;  //找不到就返回正无穷
	if(tr[p].key <= key) return get_next(tr[p].r, key);  //找到的值太小，就往右节点找
	return min(tr[p].key, get_next(tr[p].l, key));  //找到的节点值大于需要找的，那么就返回其中最小的一个
}


int main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	build();

	int n;
	cin >> n;

	for(int i = 0;i < n; ++ i)  {
		int opt, x;
		cin >> opt >> x;
		
		if(opt == 1) inser(root, x);
		else if(opt == 2) rm(root, x);
		else if(opt == 3)  cout << get_rank_by_key(root, x) - 1<< endl;  //去掉守门员的占位
		else if(opt == 4)  cout << get_key_by_rank(root,x + 1) << endl;  //抵消守门员的影响
		else if(opt == 5)  cout << get_prev(root, x) << endl; 
		else if(opt == 6)  cout << get_next(root, x) << endl;
	}
	return 0;
}

```
