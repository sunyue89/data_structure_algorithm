#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.

vector<int> comp_prefix(const string& P){
	vector<int> rlt(P.length(),0);
	int boarder = 0;
	for(int i=1; i<rlt.size(); ++i){
		while(boarder > 0 && P[i] != P[boarder]){
			boarder = rlt[boarder-1];
		}
		if(P[i] == P[boarder])
			boarder++;
		else
			boarder = 0;
		rlt[i] = boarder;
	}
	return rlt;
}
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself
	string S = pattern + "$" + text;
	vector<int> s = comp_prefix(S);
	int p = pattern.length();
	for(int i=p+1; i<S.length(); ++i){
		if(s[i] == p)
			result.push_back(i-2*p);
	}
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
