#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
struct Type {
	char letter;
	int order;
};
struct Node {
	char data;
	Node* left;
	Node* right;
};
class Tree {
private:
	Node* newNode(char _data) {
		Node* temp = new Node;
		temp->data = _data;
		temp->left = temp->right = NULL;
		return temp;
	}
	Node* _insert(vector<Type> arr, Node* node, int index) {
		if (index < arr.size()) {
			Node* temp = newNode(arr[index].letter);
			node = temp;
			
			node->left = _insert(arr, node->left, index * 2 + 1);
			node->right = _insert(arr, node->right, index * 2 + 2);
		}
		return node;
	}
public:
	Node* root;
	void insert(vector<Type> arr) {
		root = _insert(arr, root, 0);
	}
};
void print(Tree tree) {
	queue<Node*> qu;
	qu.push(tree.root);
	while (!qu.empty()) {
		cout << qu.front()->data;
		if (qu.front()->left) qu.push(qu.front()->left);
		if (qu.front()->right) qu.push(qu.front()->right);
		qu.pop();
	}
}
void swap(Type& a, Type& b) {
	Type temp = a;
	a = b;
	b = temp;
}
int partition(vector<Type>& arr, int left, int right) {
	int loc = left;
	while (true) { 
		while (arr[right].order >= arr[loc].order && loc != right) {	//arr[right] >= arr[loc]
			right--;
		}
		if (loc == right) return loc;
		else {	//loc > right
			swap(arr[loc], arr[right]);
			loc = right;
		}
		while (arr[loc].order >= arr[left].order && loc != left) {	//arr[loc] >= arr[left]
			left++;
		}
		if (loc == left) return loc;
		else{	//left > loc
			swap(arr[loc], arr[left]);
			loc = left;
		}
	}
}
void quickSort(vector<Type>& arr, int begin, int end) {
	if (begin < end) {
		int loc = partition(arr, begin, end);
		quickSort(arr, begin, loc - 1);
		quickSort(arr, loc + 1, end);
	}
}
int main(void) {
	vector<Type> arr;
	Tree tree;
	string str;
	getline(cin, str);
	Type temp;
	int order = 0;
	str += ';';
	for (int i = 0; str[i] != '\0'; ++i) {		
		if (str[i] == ' ') { temp.letter = str[i - 1]; order = 0; }
		else if (str[i] == ';') { temp.order = order; arr.push_back(temp);}
		else {
			order *= 10;
			order += str[i] - '0';
		}
	}
	quickSort(arr, 0, arr.size() - 1);
	tree.insert(arr);
	print(tree);
}