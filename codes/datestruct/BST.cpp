#include <bits/stdc++.h>
using namespace std;

// 定义树节点结构体
struct Node {
    int key;        // 节点存储的关键字（数据）
    int height;     // 节点高度，用于AVL平衡因子的计算
    Node *left;     // 左子树指针
    Node *right;    // 右子树指针
    // 构造函数：初始化节点
    Node(int v) : key(v), height(1), left(nullptr), right(nullptr) {}
};

// ---------- 一些辅助函数 ----------

// 获取节点高度，空节点高度为0
int height(Node* n) { return n ? n->height : 0; }

// 更新节点的高度（1 + 左右子树高度最大值）
void updateHeight(Node* n) { 
    n->height = 1 + max(height(n->left), height(n->right)); 
}

// 获取节点的平衡因子（左子树高度 - 右子树高度）
int getBalance(Node* n) { 
    return n ? height(n->left) - height(n->right) : 0; 
}

// ---------- 旋转操作：保持AVL平衡 ----------

// 右旋操作（用于LL型）
Node* rightRotate(Node* y) {
    Node* x = y->left;   // y的左子树为x
    Node* T2 = x->right; // 保存x的右子树

    // 执行旋转
    x->right = y;
    y->left = T2;

    // 更新高度
    updateHeight(y);
    updateHeight(x);

    // 返回新的根节点
    return x;
}

// 左旋操作（用于RR型）
Node* leftRotate(Node* x) {
    Node* y = x->right;  // y为x的右子树
    Node* T2 = y->left;  // 保存y的左子树

    // 执行旋转
    y->left = x;
    x->right = T2;

    // 更新高度
    updateHeight(x);
    updateHeight(y);

    // 返回新的根节点
    return y;
}

// ---------- 构建二叉排序树（BST） ----------
// 普通二叉搜索树插入函数（不考虑平衡）
Node* insertBST(Node* root, int key) {
    if (!root) return new Node(key); // 空树则新建节点
    if (key < root->key) 
        root->left = insertBST(root->left, key);
    else if (key > root->key)
        root->right = insertBST(root->right, key);
    // 如果等于root->key，不插入（题目保证互不相等）
    return root;
}

// ---------- 构建平衡二叉树（AVL树） ----------
Node* insertAVL(Node* node, int key) {
    // 普通BST插入
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node; // 不插入重复节点

    // 更新高度
    updateHeight(node);

    // 计算平衡因子
    int balance = getBalance(node);

    // 根据平衡因子判断失衡类型并进行旋转
    // LL型：左子树太高，且key插在左子树的左边
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR型：右子树太高，且key插在右子树的右边
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR型：左子树太高，但key插在左子树的右边
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL型：右子树太高，但key插在右子树的左边
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // 返回调整后的节点
    return node;
}

// ---------- 计算查找比较次数 ----------
// 每成功查找一个数据时，计算比较次数（每访问一个结点比较一次）
int countComparisons(Node* root, int key) {
    int cnt = 0;
    while (root) {
        ++cnt;  // 访问一个节点，计一次比较
        if (key < root->key)
            root = root->left;
        else if (key > root->key)
            root = root->right;
        else
            return cnt; // 找到该节点，返回比较次数
    }
    return cnt; // 理论上不会发生（所有key都存在）
}

// ---------- 主函数 ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n; // 读取节点数量

    // 读取第二行数据，兼容“逗号或空格”分隔
    string line;
    getline(cin, line);            // 读取第一行后面的换行符
    getline(cin, line);            // 读取真正的数据行
    for (char &c : line)
        if (c == ',') c = ' ';     // 把逗号替换为空格
    stringstream ss(line);

    vector<int> a;
    int x;
    while (ss >> x) a.push_back(x); // 读入所有整数

    // 构建BST与AVL
    Node *bst = nullptr, *avl = nullptr;
    for (int val : a) {
        bst = insertBST(bst, val);
        avl = insertAVL(avl, val);
    }

    // 计算两个树的查找比较总次数
    long long bst_sum = 0, avl_sum = 0;
    for (int val : a) {
        bst_sum += countComparisons(bst, val);
        avl_sum += countComparisons(avl, val);
    }

    // 按题目要求格式输出
    cout << "BST-ASL:" << bst_sum << "\n";
    cout << "AVL-ASL:" << avl_sum << "\n";

    return 0;
}
