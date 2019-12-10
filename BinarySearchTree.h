
#include "TreeNode.h"
#include <iostream>
#include <queue>

class BinarySearchTree
{
	friend class TransferWindowManager;
private:
	TreeNode * m_root;

public:
	BinarySearchTree() { m_root = NULL; }
	~BinarySearchTree() { free_memory(m_root); }
	
	// ���̷��� �Լ�
	void insert(SoccerPlayerData& data);
	void deletion(int ability); // ability = key

	// �߰��� �Լ�
	TreeNode* insert_c(TreeNode* root, SoccerPlayerData& data);
	TreeNode* deletion_c(TreeNode* root, int ability); // ability = key
	TreeNode* findMax(TreeNode* root);

	void in_order(std::ostream& os, TreeNode* root) const;
	void free_memory(TreeNode* root);
	void make_vector(std::vector<SoccerPlayerData>& arr);
	void push_vector(std::vector<SoccerPlayerData>& arr, TreeNode* root);

	friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree)
	{
		// fill in your code to print in-order traversal of a binary search tree

		//os << tree.m_root;
		tree.in_order(os, tree.m_root);

		return os;
	}
};
