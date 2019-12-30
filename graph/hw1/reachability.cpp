#include <iostream>
#include <vector>

using std::vector;
using std::pair;


int reach_rec(vector<vector<int>> adj, int x, int y,vector<bool> &vis){

  //std::cout<<x+1<<" "<<y+1<<std::endl;
  if(x!=y){ 
    vis[x] = true;
    for (size_t i=0;i<adj[x].size();++i){
      if(!vis[adj[x][i]])
	if(reach_rec(adj,adj[x][i],y,vis)) return true;	
    }
  }else{
    return true;
  }
  return false;
}

int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  vector<bool> visited(adj.size());
  return reach_rec(adj,x,y,visited);
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
