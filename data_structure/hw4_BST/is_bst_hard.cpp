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

bool IsBST_rec(const vector<Node> &tree, int idx, int min, int max){
	if (idx==-1) return true;

	if( (min !=0 && tree[idx].key < min) || (max !=0 && tree[idx].key >= max)){
		return false;
	}
	
	if(!IsBST_rec(tree,tree[idx].left,min,tree[idx].key) || !IsBST_rec(tree,tree[idx].right,tree[idx].key,max)) {
		return false;
	}

	return true;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  int min =0, max = 0;
  return IsBST_rec(tree,0,min,max);
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
