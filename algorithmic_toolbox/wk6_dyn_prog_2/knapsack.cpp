#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  int n = w.size();
  vector<vector<int>> value(W+1, vector<int>(n+1) ); // W+1 rows, n+1 columns

  for(int i =1; i<=n; ++i){
	  for(int j=1; j<=W; ++j){
	  	value[j][i] = value[j][i-1];
		int tmp_idx = i-1;
		if (w[tmp_idx]<=j){
			int val = value[j-w[tmp_idx]][i-1] + w[tmp_idx];
			if (value[j][i] < val) value[j][i] = val;
		}
	  }
  }
  /*debugging
  for(int i=0; i<=n; ++i){
  	 for(int j=0; j<=W; ++j){
		 std::cout<<value[j][i];
	 }
	 std::cout<<std::endl;
  }*/

  return value[W][n];

  
  /*
  int current_weight = 0;
  for (size_t i = 0; i < w.size(); ++i) {
    if (current_weight + w[i] <= W) {
      current_weight += w[i];
    }
  }
  return current_weight;
  */
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
