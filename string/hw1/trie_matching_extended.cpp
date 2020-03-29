#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
	bool isLeafOrpEnd() const
	{
		return ( (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA) || patternEnd );
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

typedef vector<Node> trie;

trie build_trie(const vector <string>& patterns){
  trie t;
	Node n;
	t.push_back(n);
  int idx = 0;
	for(auto pat:patterns){
		int cn = 0;
		char cc;

		for(int i=0;i<pat.length();++i){
			cc = pat.at(i);
			if(t[cn].next[letterToIndex(cc)] != NA){
				cn = t[cn].next[letterToIndex(cc)] ;
			}
			else{
				int tmp_idx = std::max(idx+1,cn+1);
				t[cn].next[letterToIndex(cc)] = tmp_idx;
				cn=idx=tmp_idx;
				Node n;
				t.push_back(n);
			}
			if((pat.length()-1)==i)	
				t[cn].patternEnd = true;
		}
		//cout<<cn<<cc<<endl;
	}
  return t;
}

int pre_trie_match(const string& text, const int idx, const trie& t){
	char cc = text.at(idx);
	int i = idx;
	int v = 0;
	while (true){
		if (t[v].isLeafOrpEnd()){
			return idx;
		}else if(i<text.length() && t[v].next[letterToIndex(cc)]!=NA){
			v = t[v].next[letterToIndex(cc)];
			i++;
			if(i<text.length())
				cc=text.at(i);
		}else{
			return -1;
		}
	}
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
	trie t = build_trie(patterns);
	//cout<<t[0].next[0]<<t[0].next[1]<<t[0].next[2]<<t[0].next[3]<< endl;
  for(int i=0; i<text.length(); ++i){
		int tmp = pre_trie_match(text,i,t);
		if (tmp !=-1)
			result.push_back(tmp);
	}
	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
