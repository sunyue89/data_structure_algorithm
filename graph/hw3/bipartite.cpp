#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
  //write your code here
	vector<int> dist(adj.size(),-1);
	queue<int> Q;

	dist[0] = 0;
	Q.push(0);

	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(auto v:adj[u]){
			if(dist[v]==-1){
				Q.push(v);
				dist[v] = dist[u]+1;
			}else if(dist[u]==dist[v]){
				return 0;
			}
		}
	}
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
