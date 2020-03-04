#include<iostream>

using namespace std;

class Tree;

class TreeNode {
public:
	TreeNode* left;
	TreeNode* right;
	char data;

	TreeNode(char data) { this->data = data, this->left = NULL, this->right = NULL; }
};

class Tree {
public:
	Tree() {}
	TreeNode* SearchNode(TreeNode** root, char a) {
		if (*root) {
			if ((*root)->data == a)
				return *root;
			else {
				TreeNode* tmp = SearchNode(&(*root)->left, a);
				if (tmp)
					return tmp;
				return SearchNode(&(*root)->right, a);
			}
		}
		return NULL;
	}
	void InsertNode(TreeNode** root, char a, char b, char c) {
		TreeNode* node = new TreeNode(a);
		if (*root == NULL) {
			*root = node;
		}
		else
			node = SearchNode(root, a);
		if (b != '.')
			node->left = new TreeNode(b);
		if (c != '.')
			node->right = new TreeNode(c);
	}

	void InOrder(TreeNode* node) {
		if (node) {
			InOrder(node->left);
			cout << node->data;
			InOrder(node->right);
		}
	}
	void PreOrder(TreeNode* node) {
		if (node) {
			cout << node->data;
			PreOrder(node->left);
			PreOrder(node->right);
		}
	}
	void PostOrder(TreeNode* node) {
		if (node) {
			PostOrder(node->left);
			PostOrder(node->right);
			cout << node->data;
		}
	}

};
int main()
{
	int n;
	cin >> n;
	TreeNode* root = NULL;
	Tree tree;
	while (n--) {
		char a, b, c;
		cin >> a >> b >> c;

		tree.InsertNode(&root, a, b, c);
	}

	tree.PreOrder(root);
	cout << endl;
	tree.InOrder(root);
	cout << endl;
	tree.PostOrder(root);
	cout << endl;

	return 0;
}