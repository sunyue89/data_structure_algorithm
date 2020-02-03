#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

class DisjointSetsElement {

public:
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

class DisjointSets {

public:
	int size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int x) {
		// find parent and compress path
		/* previous method only finds the parent
		while (table != sets[table].parent) table = sets[table].parent;
		return table;*/
		//compress path implementation
		if (x != sets[x].parent) sets[x].parent = getParent(sets[x].parent);
		return sets[x].parent;
	}

	void merge(int destination, int source, int &ultra_parent) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			// if sets[realDestination].rank > sets[realSource]
			// merge two components
			// use union by rank heuristic
                        // update max_table_size
			// Not using uion by rank heuristic but brute force merge instead
			sets[realSource].parent = realDestination;
			sets[realDestination].rank = max (sets[realSource].rank + 1, sets[realDestination].rank);
			sets[realDestination].size += sets[realSource].size;
			ultra_parent = realDestination;
		}		
	}
};

class Edge{

public:
	int src,dest;
	double weight;

	Edge(int x, int y, double w): src(x),dest(y),weight(w) {}
};

bool CompEdge(Edge e1, Edge e2){
	return (e1.weight<e2.weight);
}


double clustering(vector<int> x, vector<int> y, int k) {
  //write your code here
	//creating disjoint sets with single vertex elements
	DisjointSets V(x.size());
	vector <Edge> E;
	//creating edge vectors
	for(int i=0;i<x.size();++i){
		for(int j=i+1;j<x.size();++j){
			Edge e(i,j,sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2))); 
			E.push_back(e);
		}
	}
	//Sort all edges based on weight
	sort(E.begin(),E.end(),CompEdge);

	//Kruskal's algorithm adoption

	//For debugging purpose only
	int parent;

	int clusno = 0;

	for(auto e:E){
		int p1= V.getParent(e.src);
		int p2= V.getParent(e.dest);

		if( p1 != p2 ){

			if((x.size()-clusno) <= k )	return e.weight;

			V.merge(p1,p2,parent);

			#if 0
			//debug
			cout<<e.src<<" "<<e.dest<<endl;
			cout<<p1<<" "<<p2<<endl;
			cout<<parent<<" "<<e.weight<<endl;
			#endif

			clusno++;

			//debug
			//cout<<clusno<<endl;
			//cout<<endl;
		}
	}
	return -1;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
