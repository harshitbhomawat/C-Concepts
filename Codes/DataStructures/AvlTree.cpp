#include <iostream>
using namespace std;

template <typename T1, typename T2> class Node {
public:
    Node(T1 _key, T2 _val) : key(_key), val(_val) {
		left = NULL;
		right = NULL;
	}
    T1 key;
    T2 val;
    Node *left, *right;
};

template <typename T1, typename T2> class Tree {
    void InsertPvt(Node<T1,T2>* node, pair<T1, T2>& pr) {
        if (pr.first == node->key) {
            node->val = pr.second;
            return;
        } else if (pr.first < node->key) {
            if (node->left == NULL) {
                Node<T1,T2>* nn = new Node<T1,T2>(pr.first, pr.second);
                node->left = nn;
                return;
            }
            InsertPvt(node->left, pr);
        } else {
            if (node->right == NULL) {
                Node<T1,T2>* nn = new Node<T1,T2>(pr.first, pr.second);
                node->right = nn;
                return;
            }
            InsertPvt(node->right, pr);
        }
    }

    void PrintPvt(Node<T1,T2>* node) {
        if (node == NULL)
            return;
        PrintPvt(node->left);
        cout << "K: " << node->key << " V:" << node->val << endl;
        PrintPvt(node->right);
    }

public:
    Node<T1, T2>* root;
	Tree()
	{
		root = NULL;
	}
    void Insert(pair<T1, T2> pr) {
        if (root == NULL) {
            root = new Node<T1,T2>(pr.first, pr.second);
            return;
        }
        InsertPvt(root, pr);
    }

    void Print() { PrintPvt(root); }
};

int main() {
    Tree<int, int> tree;
	pair<int,int> p(1,3);
    tree.Insert(p);
	p.first = 8;
	p.second = 1;
    tree.Insert(p);
	p.first = 5;
	p.second = 15;
    tree.Insert(p);
	p.first = 1;
	p.second = 8;
    tree.Insert(p);
    tree.Print();
}
