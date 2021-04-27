#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
	int NA = 0, NC = 0, NG = 0, NT = 0, N$ = 0;
	occ_count_before['A'].push_back(0);
	occ_count_before['C'].push_back(0);
	occ_count_before['G'].push_back(0);
	occ_count_before['T'].push_back(0);
	occ_count_before['$'].push_back(0);

	for(int i=0; i<bwt.length(); ++i){
		char s = bwt[i];
		switch (s){
			case 'A':
				NA++;
			break;
			case 'C':
				NC++;
			break;
			case 'G':
				NG++;
			break;
			case 'T':
				NT++;
			break;
			case '$':
				N$++;
			break;
			default:
			break;
		}
		occ_count_before['A'].push_back(NA);
		occ_count_before['C'].push_back(NC);
		occ_count_before['G'].push_back(NG);
		occ_count_before['T'].push_back(NT);
		occ_count_before['$'].push_back(N$);
	}
	starts['$'] = 0;
	starts['A'] = N$;
	starts['C'] = starts['A'] + NA;
	starts['G'] = starts['C'] + NC;
	starts['T'] = starts['G'] + NG;
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     map<char, int>& starts, 
                     map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
	int top = 0;
	int bottom = bwt.length()-1;
	int j = pattern.length()-1;
	while(top <= bottom){
		if(j>=0){
			char s = pattern[j];
			j--;
			if(occ_count_before[s][top+1] < occ_count_before[s][bottom+1] || occ_count_before[s][top] < occ_count_before[s][bottom+1] ){
				top = starts[s] + occ_count_before[s][top];
				bottom = starts[s] + occ_count_before[s][bottom+1] -1;
			}else{
				return 0;
			}
		}else{
			return bottom-top+1;
		}
	}
  return 0;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
