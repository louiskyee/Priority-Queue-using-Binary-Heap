#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
char reletter = -1;
int reorder = -1;
class Type {
public:
	char letter = reletter;
	int order = reorder;
	friend bool operator==(Type a, Type b) {
		if (a.letter == b.letter && a.order == b.order) return true;
		return false;
	}
};
struct Node{
	Type data;
	Node* left;
	Node* right;
	Node* parent;
	int N = 0;
};
class Tree {
private:	
	Node* newNode() {
		Node* temp = new Node;
		temp->data.letter = reletter;
		temp->data.order = reorder;
		temp->left = temp->right = temp->parent = NULL;
		return temp;
	}
	void swap(Type& a, Type& b) {
		Type temp = a;
		a = b;
		b = temp;
	}
	void inspect(Node* _node) {
		if (_node->parent) {
			if (_node->data.order < _node->parent->data.order) {
				swap(_node->data, _node->parent->data);
			}
			inspect(_node->parent);
		}
	}
	void _insert(queue<Node*>& _qu, Type _data) {
		_qu.front()->data = _data;
		_qu.front()->parent->N++;
		_qu.front()->left = newNode(); _qu.front()->left->parent = _qu.front();
		_qu.front()->right = newNode(); _qu.front()->right->parent = _qu.front();
		_qu.push(_qu.front()->left);
		_qu.push(_qu.front()->right);
		inspect(_qu.front());
		_qu.pop();
	}
	Node* _delete_empty(Node* _node) {		
		if (_node->left) { _node->left = _delete_empty(_node->left); }
		if (_node->right) {	_node->right = _delete_empty(_node->right); }
		if (_node->data.order == reorder) {
			delete[] _node;
			_node = NULL;
		}
		return _node;
	}
	Node* arrange(Node* _node) {
		if (_node->left && _node->right) {
			if (_node->left->data.order < _node->right->data.order) {
				swap(_node->left->data, _node->data);
				_node->left = arrange(_node->left);
			}
			else {
				swap(_node->right->data, _node->data);
				_node->right = arrange(_node->right);
			}
		}
		else if (_node->left) {
			swap(_node->left->data, _node->data);
			_node->left = arrange(_node->left);
		}
		else if (_node->right) {
			swap(_node->right->data, _node->data);
			_node->right = arrange(_node->right);
		}
		else {
			delete[] _node;
			_node = NULL;
		}
		return _node;
	}
public:
	Node* root = NULL;
	queue<Node*> qu;
	void insert(Type _data) {
		if (root == NULL) {
			root = newNode();
			root->data = _data;
			root->left = newNode(); root->left->parent = root;
			root->right = newNode(); root->right->parent = root;
			qu.push(root->left);
			qu.push(root->right);
		}
		else {
			_insert(qu, _data);
		}
	}
	void delete_empty() {
		if (root) {
			root = _delete_empty(root);
		}
	}
	void print() {
		while (root != NULL) {
			cout << root->data.letter;
			root = arrange(root);
		}		
	}
};
int main(void) {
	Tree tree;
	string str;
	getline(cin, str);
	Type temp;
	int order = 0;
	str += ';';
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == ' ') { temp.letter = str[i - 1]; order = 0; }
		else if (str[i] == ';') {
			temp.order = order;
			tree.insert(temp); 
		}
		else {
			order *= 10;
			order += str[i] - '0';
		}
	}
	tree.delete_empty();
	tree.print();
}
