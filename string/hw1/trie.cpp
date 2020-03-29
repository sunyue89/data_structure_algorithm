#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;


trie build_trie(vector<string> & patterns) {
  trie t;
	// t[i] all edges in the format of (node,char) from node i

	/*
	edges tmp_map;
	tmp_map[' '] = 0;
	t.push_back(tmp_map);*/

	t.resize(1);
  int idx = 0;
	for(auto pat:patterns){
		int cn = 0;

		for(int i=0;i<pat.length();++i){
			char cc = pat.at(i);
			edges::iterator it = t[cn].find(cc);
			if(it!=t[cn].end()){
				cn = it->second;
			}
			else{
				int tmp_idx = std::max(idx+1,cn+1);
				/*
				edges tmp_map;
				tmp_map[cc] = tmp_idx;

				edges::iterator it = t[cn].begin();
				t[cn].insert(it, tmp_map);*/
				t[cn][cc] = tmp_idx;

				cn=idx=tmp_idx;
				t.resize(cn+1);
			}
		}
	}
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
