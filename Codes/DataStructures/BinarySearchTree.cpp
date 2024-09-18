#include<iostream>
#include<string>
#include<sstream>

template<typename T>
struct Node
{
	T val;
	Node* left, *right;
	Node(T val_ = 0,Node* left_ = NULL,Node* right_ = NULL):val(val_),left(left_),right(right_)
	{};
};

template<typename T>
class BST;

template<typename T>
std::ostream& operator <<(std::ostream &ost,BST<T>& tree); //pre-declaration is required because of friend class.

template<typename T>
class BST
{
private:
	Node<T>* root;
	int size;

	Node<T>* RemoveInternal(Node<T>* node,T x)
	{
		if(node == NULL)
		{
			return node;
		}
		if(node->val < x)
		{
			node -> right = RemoveInternal(node->right,x);
			return node;
		}
		else if(node->val > x)
		{
			node -> left = RemoveInternal(node->left,x);
			return node;
		}
		if(node -> right == NULL)
		{
			Node<T>* temp = node->left;
			delete node;
			return temp;
		}
		
		if(node -> left == NULL)
		{
			Node<T>* temp = node->right;
			delete node;
			return temp;
		}
		
		Node<T>* temp = node->right;
		Node<T>* tempPar = node;
		while(temp->left != NULL)
		{
			tempPar = temp;
			temp = temp->left;
		}
		node->val = temp->val;
		tempPar->left = NULL;
		delete temp;
		return node;
	}

	void printInorder(Node<T>* node,std::stringstream& ss)
	{
		if(node->left != NULL)
			printInorder(node->left,ss);
		ss<<node->val<<",";
		if(node->right!=NULL)
			printInorder(node->right,ss);
	}

	std::string Print()
	{
		std::stringstream ss;
		printInorder(root,ss);
		//std::cout<<ss.str()<<endl;
		return ss.str();
	}
public:
	BST():root(NULL),size(0)
	{};
	friend std::ostream& operator<< <T>(std::ostream &ost,BST<T>& tree);
	// {
		// ost<<tree.Print();
		// return ost;
	// }
	void insert(T x)
	{
		if(root == NULL)
		{
			root = new Node<T>(x);
			return;
		}
		Node<T>* temp = root;
		while(true)
		{
			if(x == temp->val)
			{
				std::cout<<x<<" already present in tree!";
				return;
			}
			else if(x < temp->val and temp->left!=NULL)
			{
				temp = temp->left;
				continue;
			}
			else if(x > temp->val and temp->right!=NULL)
			{
				temp = temp->right;
				continue;
			}
			break;
		}
		if(x < temp->val)
		{
			Node<T>* node = new Node<T>(x);
			temp->left = node;
		}
		else if(x > temp->val)
		{
			Node<T>* node = new Node<T>(x);
			temp->right = node;
		}
	}
	bool find(T x)
	{
		if(root == NULL)
		{
			return false;
		}
		Node<T>* temp = root;
		while(true)
		{
			if(x == temp->val)
			{
				return true;
			}
			else if(x < temp->val and temp->left!=NULL)
			{
				temp = temp->left;
				continue;
			}
			else if(x > temp->val and temp->right!=NULL)
			{
				temp = temp->right;
				continue;
			}
			break;
		}
		return false;
	}
	void Remove(T x)
	{
		if(root == NULL)
		{
			return;
		}

		root = RemoveInternal(root,x);
		return;
	}
};

template<typename T>
std::ostream& operator <<(std::ostream &ost,BST<T>& tree)
{
	ost<<tree.Print();
	return ost;
} 

int main()
{
	BST<double> tree;
	tree.insert(2.3);
	tree.insert(7.4);
	tree.insert(7.3);
	tree.insert(3);
	tree.insert(1.1);
	tree.insert(9);
	tree.insert(7.5);
	tree.insert(4);
	tree.insert(6);
	tree.Remove(7.4);
	std::cout<<tree<<std::endl;

	return 0;
}
