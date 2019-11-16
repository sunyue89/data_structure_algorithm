#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool sort_oprt(string i, string j){ 

	/*
	if (i.length() <= j.length()){
		for(int tmp=i.length(); tmp<j.length(); tmp++)
			i += i.back();
	}
	else{
		for(int tmp=j.length(); tmp<i.length(); tmp++)
			j += j.back();
	}
	this algorithm does not work for the edge case of 58 v.s. 588 
	*/
	string tmp = i;
	i = i + j;
	j = j + tmp;
	return i>j;

}

string largest_number(vector<string> a) {
  //write your code here
  sort(a.begin(),a.end(),sort_oprt);
  std::stringstream ret;
  for (size_t i = 0; i < a.size(); i++) {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
