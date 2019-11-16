#include <iostream>

int get_change(int m) {
  //write your code here
  int a = 0;
  //vector <int> change = {10,5,1};
  int n = m/10 + (( a = m%10 )/5) + ( (a%5)/1 ); 
  return n;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
