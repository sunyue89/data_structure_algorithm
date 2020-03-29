#include <iostream>
#include <cassert>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

int const Letters =    5;
//int const Type 		= 	 3;
//int const StId 		=		 0;
//int const Lgth		=		 1;
//int const EdId		=		 2;
int const NA      =   -1;


struct Node
{
	//	vector<vector<int>> Edges;
	vector<int> NextNode;
	int Parent;
	int Depth;
	int Start;
	//vector<int> Next[Letters];

	//Node() : Edges(Letters,vector<int>(Type)), NextNode(Letters)
	Node() : NextNode(Letters), Parent(0), Depth(0), Start(0)
	{
		/*
		for(int i=0;i<Edges.size();++i)
		{
			Edges[i] = {NA,NA,NA};//start,depth,initial w/ the starting letter
		}*/
		for(int i=0;i<NextNode.size();++i)
		{
			NextNode[i] = NA;//child of node w/ the starting letter
		}
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
		case '$': return 4; break;
		default: assert (false); return -1;
	}
}

typedef vector<Node> SufTree;

SufTree build_tree(const string& text){

  SufTree t;
	Node n;
	t.push_back(n);


	for(int i=0;i<text.length();++i){
		int cn = 0;
  	int d = 0;
		int tmp_idx = 0;
		//char ci = text.at(i);
	
		while (d == t[cn].Depth && t[cn].NextNode[letterToIndex(text[i+d])] !=NA){
			cn = t[cn].NextNode[letterToIndex(text[i+d])];
			d++;
			while (d<t[cn].Depth && text[t[cn].Start+d] == text[i+d]){
				d++;
			}
		}
		if (d<t[cn].Depth){
			int cp = t[cn].Parent;
			Node v;
			tmp_idx = t.size();
			v.Start = i;
			v.Depth = d;
			v.NextNode[letterToIndex(text[t[cn].Start+d])] = cn;
			t[cn].Parent = tmp_idx;
			t[cp].NextNode[letterToIndex(text[i+t[cp].Depth])] = tmp_idx;
			v.Parent = cp;	
			t.push_back(v);
			cn = tmp_idx;
		}
		Node w;
		tmp_idx = t.size();
		w.Start = i;
		w.Depth = text.length()-i+1;
		t[cn].NextNode[letterToIndex(text[i+d])] = tmp_idx;
		w.Parent = cn;
		t.push_back(w);

		#if 0
	  int tmp_char_idx = 0;
		int tmp_sft_idx = i;
		int k = 1;

		for(int j=i;j<text.length();++j){
	
			char cc = ci;
			if (j<text.length()-1)
				cc = text.at(j+1);
			vector<int> tmp_edge = {0,0,0};

			if(t[cn].Edges[letterToIndex(ci)][0] != NA){
		
				tmp_edge = t[cn].Edges[letterToIndex(ci)];
				tmp_char_idx = tmp_edge[0];

				if(text.at(tmp_char_idx+1)!=cc){
					//create a node
					if(t[cn].NextNode[letterToIndex(ci)]==NA){
						int tmp_idx = t.size();
						t[cn].Edges[letterToIndex(ci)][1] = k;//update the length of split
						t[cn].NextNode[letterToIndex(ci)] = tmp_idx;
						cn = tmp_idx;
						ci = cc;
						Node n;
						t.push_back(n);
						t[cn].Edges[letterToIndex(text.at(tmp_char_idx+k))] = {tmp_char_idx+k,tmp_edge[1]-k,tmp_edge[2]};
					}else{
						cn = t[cn].NextNode[letterToIndex(ci)];
						ci = cc;
					}
				}else{
					k++;
					//cout<<k<<endl;
				}
				tmp_sft_idx = j+k;
			}
			else{
				//keep walking to end to create an edge
				if(4==letterToIndex(text.at(j))){
					t[cn].Edges[letterToIndex(ci)] = {/*tmp_char_idx+*/tmp_sft_idx,j-tmp_sft_idx+1,tmp_sft_idx};
				}		
			}
		}
		#endif
	}
	//cout<<cn<<cc<<endl;
  return t;
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
	SufTree t =  build_tree(text);
	#if 0
	for (int i=0;i<t.size();++i)
			for (int j=0;j<t[i].Edges.size();++j)
				if(t[i].Edges[j][0]!=NA){
					result.push_back(text.substr(t[i].Edges[j][0],t[i].Edges[j][1]));
					//cout<<t[i].Edges[j][0]<<endl;
				}
	#endif
	for (int i=1;i<t.size();++i)
				result.push_back(text.substr(t[i].Start+t[t[i].Parent].Depth, t[i].Depth - t[t[i].Parent].Depth));

  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
