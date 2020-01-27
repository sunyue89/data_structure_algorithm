#include <iostream>
#include <vector>

using std::vector;

const int INF = 1001;//2147483647;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here
	vector<int> dist(adj.size(),INF);
	//source would be node 0
	dist[0] = 0;
	int i = 0;

	//Bellman-Ford |V| Iteration for cycle checks
	while(i<adj.size()){

		bool nc = true;
		//Edge Iteration
		for(int u=0;u<adj.size();++u){
			int j=0;
			for(auto v:adj[u]){
				if(/*dist[u] != INF &&*/ dist[v]>(dist[u]+cost[u][j])){
					dist[v] = dist[u]+cost[u][j];
					nc = false;
				}
				++j;
			}
		}
		/*
	  //debugging print
		for(auto x:dist){	
			std::cout<<x<<" ";
		}
		std::cout<<std::endl;
		*/
		//if the second iteration and above has no change, no need to proceed, return false
		if(i>0 && nc)	return 0;
		++i;
	}
	
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
