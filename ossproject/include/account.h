struct Account {
  
	int			key;	
	TreeNode	*left;			// left child 
	TreeNode	*right;			// right child 
	TreeNode(int k, TreeNode* l, TreeNode* r) {
		key = k; 	left = l;	right = r;
	}
	TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
	~TreeNode() {}
};

using account = Account*;
