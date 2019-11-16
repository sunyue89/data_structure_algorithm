#include <iostream>
#include <vector>

using std::vector;

int lcs2(vector<int> &a, vector<int> &b) {
  //write your code here
  int n = a.size();
  int m = b.size();
  vector<vector<int>> score(n+1,vector<int> (m+1,0));
  for (int i=1;i<=n;++i){
  	for(int j=1;j<=m;++j){
		if(a[i-1] == b[j-1]){ 
			score[i][j] = score[i-1][j-1] + 1;
		}
		else{
			score[i][j] = std::max(score[i-1][j],score[i][j-1]);
		}
	}
  }
  return score[n][m];
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
