#include <iostream>
#include <vector>
#include <math.h>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  int strt = int (sqrt(2*n)) - 1;

  while ( (strt+1)*(strt+2) <= 2*n) 
	  strt++;

  for(int i=1;i<strt;i++)
  	summands.push_back(i);
  summands.push_back(n - strt*(strt-1)/2);

  //write your code here
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
