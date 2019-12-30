#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void reach_rec(vector<vector<int>> adj, int x,vector<bool> &vis){

  //std::cout<<x+1<<" "<<y+1<<std::endl;
    vis[x] = true;
    for (size_t i=0;i<adj[x].size();++i){
      if(!vis[adj[x][i]])
	reach_rec(adj,adj[x][i],vis);
    }
}


int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  vector<bool> visited(adj.size());
  for(size_t i=0;i<adj.size();++i){
    if(!visited[i]){
	reach_rec(adj,i,visited);
	res++;
    }
  }
  //write your code here
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
