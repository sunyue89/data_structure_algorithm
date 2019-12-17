#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBST_rec(const vector<Node> &tree, int idx, int &value){
	if (idx==-1) return true;

	if(!IsBST_rec(tree,tree[idx].left,value)) return false;

	if(value !=0 && tree[idx].key <= value){
		return false;
	}
	value = tree[idx].key;
	if(!IsBST_rec(tree,tree[idx].right,value)) return false;

	return true;
}
bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  int key_val = 0;
  return IsBST_rec(tree,0,key_val);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  if(nodes>0){
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  }
  if (nodes ==0 || IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
