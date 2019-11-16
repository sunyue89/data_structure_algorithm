#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
//	a(n)
// a(1:n/2) a(n/2:n)
//
// a(1:2).. a(3:4).. a(n-1:n)
//a(1) a(2) .............. a(n)
//
//2 3 9 2 2
//mid = 2
//call (a, 0 1)
//call (a, 3 4)
//return a[0] 2
//return a[3] 2
unsigned int countvalue(vector<int> &a, int num, int left, int right){
	unsigned int count = 0;
	for (int i=left; i<=right; i++){
		if (a[i]==num) count++;
	}
	return count;
}

int get_majority_element(vector<int> &a, int left, int right) {
  if (left > right) return -1;
  if (left == right) return a[left];
  //write your code here
  int mid = left + (right - left)/2;

  
  int ele_lft = get_majority_element (a, left, mid); 
  int ele_rgt = get_majority_element (a, mid+1, right);

  unsigned int leftCount = countvalue(a, ele_lft, left, right);
  unsigned int rightCount = countvalue(a, ele_rgt, left, right);
 
 /* 
  if (ele_lft == ele_rgt){//both contains majority element, or either contains majority element, done
  	return ele_lft;
  }else*/ 
  if (ele_lft == -1 && ele_rgt != -1){//else if right has it
  	if (rightCount >= (right - left)/2 +1 ){
	  	return ele_rgt;
	}
	else{
		return -1;
	}
  }else if (ele_rgt == -1 && ele_lft != -1){//else if left has it
  	if (leftCount >= (right - left)/2 +1 ){
	  	return ele_lft;
	}
	else{
		return -1;
	}

  }else if (ele_lft !=-1 && ele_rgt !=-1){
	//return (leftCount >rightCount? ele_lft:ele_rgt);  
  		  
  	if (leftCount >= (right - left)/2 +1 ){
	  	return ele_lft;
	}
	else if(rightCount >= (right - left)/2 +1 )
	{
	  	return ele_rgt;
	}
	else{
		return -1;
	}
  }else{
  	return -1;
  }
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
  //std::cout << get_majority_element (a, 0, a.size()) << '\n'; 

}
