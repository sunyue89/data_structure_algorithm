#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string r = "";

	int L = text.length();
  // write your code here
	vector<string> M(L);
	for(int i=0; i<L; ++i){
		M[i] = text.substr(L-i-1) + text.substr(0,L-i-1);
	}
	sort(M.begin(),M.end());
	for(int i=0; i<L; ++i){
		r += M[i].back();
	}

  return r;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
