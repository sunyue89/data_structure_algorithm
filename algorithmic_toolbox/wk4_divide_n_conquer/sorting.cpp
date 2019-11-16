#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

void partition3(vector<int> &a, int l, int r, int &m, int &n){
  int x = a[l];
  m = l, n = r;
  int i = l;
  while ( i <= n){
	if (a[i] < x){
	   swap(a[i],a[m]);
	   i++;
	   m++;
	}else if (a[i] == x){
	   i++;
	}else{
	   swap(a[i],a[n]);
	   n--;
	}
  }
}
//tested to be a wrong answer
void partition3_m2(vector<int> &a, int l, int r, int &m, int &n){
  int x = a[l];
  m = l; n = l;
  for (int i = l + 1; i <= r; i++) {
	if(a[i] <= x){
  		if (a[i] < x) {
     	  		m++;
	 		swap(a[i], a[m]);
    		}
	  	n++;
	}
  }
  swap(a[l], a[m]);
}


void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  //int m = partition2(a, l, r);
  int m,n;
  partition3(a,l,r,m,n);
  randomized_quick_sort(a, l, m - 1);
  randomized_quick_sort(a, n + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
