#include <iostream>
#include <vector>

using std::vector;
using std::pair;


int cycle_rec(vector<vector<int>> adj, int x,vector<bool> &vis,vector<bool> &vis_keep){
    if(!vis_keep[x]){

      //std::cout<<x+1<<std::endl;
      //recursive stack
      vis[x] = true;
      //DFS stack
      vis_keep[x] = true;

      for (size_t i=0;i<adj[x].size();++i){
        if(!vis_keep[adj[x][i]] && cycle_rec(adj,adj[x][i],vis,vis_keep)){
	  return true;
  	}
        else if (vis[adj[x][i]]){
	  return true;
        }	
      }
    }
    vis[x] = false;
    return false;
}

int acyclic(vector<vector<int> > &adj) {
  //write your code here
  vector<bool> visited(adj.size());
  vector<bool> vis(adj.size());	
  for(size_t i=0;i<adj.size();++i){
	//std::cout<<std::endl;
	//std::cout<<i+1<<std::endl;
    if(cycle_rec(adj,i,vis,visited)){ 
	return true;
    }
  }
  return false;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
