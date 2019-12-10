#include "BinarySearchTree.h"

void BinarySearchTree::insert(SoccerPlayerData& data)
{
	//// Current node
	TreeNode* parent = NULL;
	TreeNode* current = m_root;

	if (current == NULL)
	{
		m_root = new TreeNode(data);
		return;
	}

	// Finde empty space by comparing scale
	while (current != NULL)
	{
		parent = current;

		// If small left
		if (current->m_data.m_ability > data.m_ability)
		{
			current = current->m_left;
		}
		// If large Right
		else if (current->m_data.m_ability < data.m_ability)
		{
			current = current->m_right;
		}
	}

	if (parent->m_data.m_ability > data.m_ability)
	{
		parent->m_left = new TreeNode(data);
	}
	else
	{
		parent->m_right = new TreeNode(data);
	}

	//parent->m_data.m_ability > data.m_ability ? parent->m_left : parent->m_right = new TreeNode(data);

	//insert_c(m_root, data);
}

TreeNode* BinarySearchTree::insert_c(TreeNode* root, SoccerPlayerData& data)
{
	if (root == NULL)
	{
		root = new TreeNode(data);
	}
	else
	{
		if (root->m_data.m_ability > data.m_ability)
		{
			root->m_left = insert_c(root->m_left, data);
		}
		else
		{
			root->m_right = insert_c(root->m_right, data);
		}
	}

	return root;
}

void BinarySearchTree::deletion(int ability)
{
	m_root = deletion_c(m_root, ability);
}

TreeNode* BinarySearchTree::deletion_c(TreeNode* root, int ability)
{
	TreeNode* tempNode = NULL;

	if (root == NULL)
	{
		return NULL;
	}

	// Searching by comparing size
	if (root->m_data.m_ability > ability)
	{
		root->m_left = deletion_c(root->m_left, ability);
	}
	else if (root->m_data.m_ability < ability)
	{
		root->m_right = deletion_c(root->m_right, ability);
	}
	// root.data == key
	else
	{
		// If it has 2 child
		if (root->m_left != NULL && root->m_right != NULL)
		{
			// replace by left subtree's maximumval
			tempNode = findMax(root->m_left);
			root->m_data = tempNode->m_data;

			// Delete duplicate maximum val in left subtree
			root->m_right = deletion_c(root->m_right, tempNode->m_data.m_ability);
		}
		// less than 1 child
		else
		{
			// return valid node
			// if not return just NULL
			tempNode = (root->m_left == NULL) ? root->m_right : root->m_left;
			free(root);

			return tempNode;
		}
	}

	return root;
}

TreeNode* BinarySearchTree::findMax(TreeNode* root)
{
	TreeNode* temp = root;

	while (temp->m_right != NULL)
	{
		temp = temp->m_right;
	}

	return temp;
}

void BinarySearchTree::in_order(std::ostream& os, TreeNode* root) const
{
	if (root == NULL)
	{
		return;
	}

	in_order(os, root->m_left);
	os << root << std::endl;
	in_order(os, root->m_right);
}

void BinarySearchTree::free_memory(TreeNode* root)
{
	if (root == NULL)
	{
		return;
	}

	free_memory(root->m_left);
	free_memory(root->m_right);
	free(root);
}

void BinarySearchTree::make_vector(std::vector<SoccerPlayerData>& arr)
{
	push_vector(arr, m_root);
}

void BinarySearchTree::push_vector(std::vector<SoccerPlayerData>& arr, TreeNode* root)
{
	if (root == NULL)
	{
		return;
	}

	push_vector(arr, root->m_right);
	if (arr.empty())
	{
		arr.push_back(root->m_data);
	}
	else
	{
		// during push player case : low abilty high play than ignore it
		if (arr.back().m_transfer_fee > root->m_data.m_transfer_fee)
		{
			arr.push_back(root->m_data);
		}
	}
	push_vector(arr, root->m_left);
}
