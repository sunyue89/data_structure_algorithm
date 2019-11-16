#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;


struct pack{
  int wgt, v;
  double d;
};

bool compare_pack(pack p1, pack p2)
{
  return (p1.d > p2.d);
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;


  vector<double> den;
  vector<pack> mypack;
  
  for (int i=0; i<weights.size(); i++){
  	den.push_back(double (values[i])/weights[i]);
	mypack.push_back({weights[i],values[i],den[i]});
  }
  sort(mypack.begin(), mypack.end(), compare_pack);

  int i = 0;
  int tmp = 0;
  while(capacity>0 && i<weights.size()){
  	capacity = capacity - ( tmp = std::min(capacity, mypack[i].wgt) );
	value += tmp*mypack[i].d;
	i++;
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << '\n';
  //for (auto x : debug)
  //	 std::cout << x.wgt << " " << x.v << " " << x.d << std::endl;

  return 0;
}
