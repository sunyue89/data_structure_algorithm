#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::greater;
using std::make_pair;

const int INF = 2147483647;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
	vector<int> dist(adj.size(),INF);
	dist[s] = 0;
	/*
	for(auto x:dist){	
		std::cout<<x<<" ";
	}
	std::cout<<std::endl;
	*/
	priority_queue < pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;
  pq.push(make_pair(dist[s],s));
	while(!pq.empty()){
		pair<int,int> ndp = pq.top();
		pq.pop();
		int u = ndp.second;
		//std::cout<<u+1<<" "<<dist[u]<<std::endl;
		if(t==u)	return	dist[u];
		int i=0;	
		for(auto v:adj[u]){
			if(dist[v]> (dist[u]+cost[u][i])){
				dist[v] = dist[u]+cost[u][i];
				pq.push(make_pair(dist[v],v));
			}
			++i;
		}
	}	
  return -1;
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
