#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
  //write your code here
  used[x] = true;
  for(size_t i=0;i<adj[x].size();++i){
	if(!used[adj[x][i]])
		dfs(adj,used,order,adj[x][i]);
	}
  order.insert(order.begin(),x);
  return;
  
}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  //write your code here
  for(size_t i =0; i<adj.size(); ++i){
	if(!used[i]){
		dfs(adj,used,order,i); 
	}
  }
  return order;
}

vector<vector<int>> rev(vector<vector<int>> adj){
  vector<vector<int>> trav(adj.size(),vector<int>());
  for (size_t i=0; i<adj.size(); ++i){
	for (size_t j=0; j<adj[i].size();++j)
		trav[adj[i][j]].push_back(i);
  } 
  return trav;
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {

  int result = 0;
  //write your code here
	vector<vector<int>> adj_r = rev(adj);
	vector<int> dfs_r = toposort(adj_r);
	vector<int> visited(adj.size(),0);
	vector<int> order;

	for(auto v:dfs_r){
		if(!visited[v]){
			dfs(adj,visited,order,v);
			result++;
		}
	}
  return result;
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
  std::cout << number_of_strongly_connected_components(adj);
}
