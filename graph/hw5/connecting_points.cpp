#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

const double INF = 100000.;

double cal_dist(int x1, int y1, int x2, int y2){
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

bool AllNodesChecked(vector<bool> set){
	bool tmp = true;
\
	for(int i=0; i<set.size(); ++i){
		tmp = tmp && set[i];
	}

	return tmp;

}

 
double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  //write your code here
	vector<double> cost(x.size(),INF);
	cost[0] = 0.;

	priority_queue < pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>> > pq;

	vector<bool> close_set(x.size(),false);

	pq.push(make_pair(cost[0],0));

	while(!pq.empty()/*&&!AllNodesChecked(close_set)*/){
		pair<double,int> ndp = pq.top();
		pq.pop();
		int u = ndp.second;
		close_set[u]=true;

		double tmp;
		for(int z=0;z<x.size();++z){
			if(!close_set[z] && (tmp=cal_dist(x[z],y[z],x[u],y[u]))<cost[z]){
				cost[z] = tmp;
				pq.push(make_pair(cost[z],z));
			}
		}
	}
	for(int i=0;i<cost.size();++i){
		//debug
		//cout<<cost[i]<<endl;
		result += cost[i];
	}
	
	
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
