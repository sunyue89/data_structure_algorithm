#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

const int INF = 2147483647;

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  //write your code here
	distance[s] = 0;
	reachable[s] = 1;
	shortest[s] = 1;

	int i=0;

		//Bellman-Ford |V-1| Iteration for cycle checks
	while(i<(adj.size()-1)){

		//Edge Iteration
		for(int u=0;u<adj.size();++u){
			int j=0;
			for(auto v:adj[u]){
				if(distance[u]!=INF && distance[v]>(distance[u]+cost[u][j])){
					distance[v] = distance[u]+cost[u][j];
					if(reachable[v]!=1)	reachable[v] = 1;
				}
				++j;
			}
		}
		
	  //debugging print
		/*
		for(auto x:distance){	
			std::cout<<x<<" ";
		}
		std::cout<<std::endl;
		*/
		++i;
	}

	queue <int>	inf_Q;

	//Last Edge Iteration
	for(int u=0;u<adj.size();++u){
		int j=0;
		for(auto v:adj[u]){
			if(distance[u]!=INF && distance[v]>(distance[u]+cost[u][j])){
				distance[v] = distance[u]+cost[u][j];
				if(shortest[v]!=0)	shortest[v] = 0;
				inf_Q.push(v);
			}
			++j;
		}
	}
	
	//breadth-first search to capture all nodes that are infinite arbitrage
	while(!inf_Q.empty()){
		int u = inf_Q.front();
		inf_Q.pop();
		for(auto v:adj[u]){
			if(shortest[v]!=0){
				inf_Q.push(v);
				shortest[v]=0;
			}
		}
	}

  return;
	
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  //vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<long long> distance(n, INF);
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
