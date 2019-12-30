#include <iostream>
#include <vector>

using std::vector;
using std::pair;


void reach_rec(vector<vector<int>> adj, int x, int y,vector<bool> &vis, bool &con){

  //std::cout<<x+1<<" "<<y+1<<std::endl;
  if(x!=y){ 
    vis[x] = true;
    for (size_t i=0;i<adj[x].size();++i){
      if(!vis[adj[x][i]])
	reach_rec(adj,adj[x][i],y,vis,con);	
    }
  }else{
    con = 1;
    return;
  }
}

int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  vector<bool> visited(adj.size());
  std::cout<<std::endl;
  bool flag = false;
  reach_rec(adj,x,y,visited,flag);
  return flag;
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
