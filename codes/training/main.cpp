
#include<bits/stdc++.h>
using namespace std;
#define i128 __int128
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define fi(x) for(int i = 1; i <= x; ++i)
#define fi0(x) for(int i = 0; i < x; ++i)
#define fj(n) for(int j = 1; j <= n; ++j)
#define fj0(n) for(int j = 0; j < n; ++j)
#define caillo ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define PLEASE_AC return 0
#define startime auto start = chrono::high_resolution_clock::now();
#define endtime auto end = chrono::high_resolution_clock::now();
#define runningtime cout << "running time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<<" ms\n";
typedef long long ll;
typedef unsigned long long ull;

struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int val):val(val), left(nullptr), right(nullptr){}
};

int n;
string s;

TreeNode* build(int &i){
	if(i >= n) return nullptr;
	if(s[i] == '#') {i++;return nullptr;}
	TreeNode *node = new TreeNode(s[i++]);
	node->left = build(i);
	node->right = build(i);
	return node;
}

// 
//
const int N = 100000;
char pre[N], ino[N], pos[N];
int pr, io, po, high, lev;
void preOrder(TreeNode *root, int *size){
	if(root == NULL) return;

	pre[++pr] = root->val;
	preOrder(root->left, size);
	preOrder(root->right, size);
}

void inOrder(TreeNode* root, int *size){
	if(root == NULL) return;

	inOrder(root->left, size);
	ino[++io] = root->val;
	inOrder(root->right, size);

}

void postOrder(TreeNode* root, int *size){
	if(root == NULL) return ;

	postOrder(root->left, size);
	postOrder(root->right, size);
	pos[++po] = root->val;
}

void levelOrder(TreeNode* root){
	queue<TreeNode*> q;
	queue<TreeNode*> p;

	q.push(root);
	p.push(root);

	while(!q.empty()){
		auto cur = q.front(); q.pop();
		if(!p.empty() && cur == p.front()){
			high++;
			while(!p.empty()){
				cout << (char)p.front()->val;
				p.pop();
			}
			cout << '\n';
		}
		if(cur->left) q.push(cur->left);
		if(cur->right) q.push(cur->right);

		if(!cur->left && !cur->right) lev++;

		if(cur->left) p.push(cur->left);
		if(cur->right) p.push(cur->right);
	}

	while(!p.empty()){
		cout << (char)p.front()->val;
	}

}

signed main() {
//	freopen("an", "r", stdin);
	
	cin >> n; cin >> s;
	int init = 0;
	TreeNode* root = build(init);

	preOrder(root, &n);
	inOrder(root, &n);
	postOrder(root, &n);
	
	cout << "preorder traversal:";
	fi(pr){ cout << pre[i];} cout << '\n';
	cout << "inorder traversal:";
	fi(io){cout << ino[i];} cout << endl;
	cout << "postorder traversal:";
	fi(po){cout << pos[i];}cout << endl;

	cout << "level traversal:\n";

	levelOrder(root);
	

	cout << lev << endl;
	cout << high;

	PLEASE_AC;
}
