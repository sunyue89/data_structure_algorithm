#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

int CharMap(char c){
	int o=0;
	switch (c){
		case '$':
			o = 0;
			break;
		case 'A':
			o = 1;
			break;
		case 'C':
			o = 2;
			break;
		case 'G':
			o = 3;
			break;
		case 'T':
			o = 4;
			break;
		default:
			break;
	}
	return o;
}
void SortChar(const string& S, vector<int>& ord){
	//count sort with 5 chars, $, A, C, G, T
	vector<int> cnt(5,0);
	for(int i=0; i<S.length(); ++i)
		cnt[CharMap(S[i])]++;
	for(int j=1; j<cnt.size(); ++j)
		cnt[j] += cnt[j-1];
	for(int i=S.length()-1; i>=0; --i){
		int c = CharMap(S[i]);
		cnt[c]--;
		ord[cnt[c]] = i;
	}
}

void CompCharClasses(const string& S, vector<int>& ord, vector<int>& cls){
	cls[ord[0]] = 0;
	for(int i=1; i<S.length(); ++i){
		if(S[ord[i]] != S[ord[i-1]])
			cls[ord[i]] = cls[ord[i-1]] + 1;
		else
			cls[ord[i]] = cls[ord[i-1]];
	}
}

void BuildInit(const string& S, vector<int>& ord, vector<int>& cls){
	SortChar(S,ord);
	CompCharClasses(S,ord,cls);
}

vector<int> SortDoubled(const string& S, int L, vector<int>& ord, vector<int>& cls){
	vector<int> cnt(S.length(),0);
	vector<int> newOrd(S.length(),0);
	for(int i=0; i<S.length(); ++i)
		cnt[cls[i]]++;
	for(int j=1; j<cnt.size(); ++j)
		cnt[j] += cnt[j-1];
	for(int i=S.length()-1; i>=0; --i){
		int start = (ord[i]-L+S.length())%S.length();
		int c = cls[start];
		cnt[c]--;
		newOrd[cnt[c]] = start;
	}
	return newOrd;
}

vector<int> UpdateClasses(vector<int>& newOrd, vector<int>& cls, int L){
	int n = newOrd.size();
	vector<int> newClass(n,0);
	for(int i=1; i<n; ++i){
		int cur = newOrd[i];
		int prev = newOrd[i-1];
		int mid = (cur+L)%n;
		int midPrev = (prev+L)%n;
		if(cls[cur] != cls[prev] || cls[mid] != cls[midPrev])
			newClass[cur] = newClass[prev]+1;
		else
			newClass[cur] = newClass[prev];
	}
	return newClass;
}


// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  // Implement this function yourself
	vector<int> order(text.length(),0);
	vector<int> class_(text.length(),0);
	BuildInit(text,order,class_);
	int L = 1;
	while (L<text.length()){
		vector<int> newOrder = SortDoubled(text,L,order,class_);
		vector<int> newClass = UpdateClasses(newOrder,class_,L);
		L *= 2;
		order = newOrder;
		class_ = newClass;
	}
  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
