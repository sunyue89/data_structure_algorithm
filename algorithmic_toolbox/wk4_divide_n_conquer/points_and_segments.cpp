#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using std::vector;
using std::pair;

#if 0
bool sortbysec(const pair <int, int> &a, const pair <int, int> &b){
	return (a.second < b.second);
}

bool comp_lb(pair <int,int> i, int j){
	if (i.second < j){
		return 1;
	}else{
		return 0;
	}
}

bool comp_ub(pair <int,int> i, int j){
	if (i.first > j){
		return 1;
	}else{
		return 0;
	}
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points, vector<pair <int,int>> &debug0, vector<pair <int,int>> &debug) {
  vector<int> cnt(points.size());
  // sort <end,start> by pairs, binary search the point by end to get the min, then increment till start is greater
  vector< pair <int,int> > all_segs(0);
  for (int i=0; i< starts.size(); i++){
  	all_segs.push_back(std::make_pair(starts[i], ends[i]));
  }
  std::sort(all_segs.begin(),all_segs.end(),sortbysec);
/*
  for (auto x:all_segs){
  	debug0.push_back(x);
  }
*/
  vector< pair <int,int> >::iterator i1, i2;
  for (size_t  i=0; i< points.size(); i++){
  	i1 = std::lower_bound(all_segs.begin(), all_segs.end(), points[i],comp_lb);
	debug[i] = *i1;//;std::make_pair( (i1)->first , (i1)->second );
	int l = i1 - all_segs.begin();
	int r = all_segs.1end()-i1;
	cnt[i] = ;
	/*
	if(i1 != all_segs.end()){ 
		//if point within end range, increment till start is out of range, end will always be true
		while (i1 < all_segs.end() && (  i1->first  <= points[i] ) &&  ( i1->second  >= points[i])){
			cnt[i]++;
			i1++;
		}
	}*/
  }
  return cnt;
}
#endif

bool comp_lb(int i, int j){
	if (i<=j) return 1;
	return 0;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  
  std::sort(starts.begin(),starts.end());
  std::sort(ends.begin(),ends.end());
  
  vector<int>::iterator i1, i2;
  for (size_t  i=0; i< points.size(); i++){
  	i1 = std::lower_bound(starts.begin(), starts.end(), points[i],comp_lb);
	//debug0[i] = *i1;	
	i2 = std::lower_bound(ends.begin(),ends.end(),points[i]);
	//debug[i] = *i2;
	int l = i1 - starts.begin();
	int r = ends.end()-i2;
	cnt[i] = l+r-starts.size();
  }
  return cnt;
}


vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  #if 0
  vector< pair <int,int> > debug0(0);
  vector< pair <int,int> > debug(points.size());
  #endif
  //use fast_count_segments
  //vector<int> cnt = naive_count_segments(starts, ends, points);
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
  /*
  std::cout << '\n';
  std::cout << "--------------------"<< '\n';
   for (vector <pair<int,int>>::iterator i = debug0.begin(); i < debug0.end(); i++) {
    std::cout << i->first << ' ' << i->second << '\n';
  }  
     std::cout << "--------------------"<< '\n';

   for (vector <pair<int,int>>::iterator i = debug.begin(); i < debug.end(); i++) {
    std::cout << i->first << ' ' << i->second << '\n';
  }
  */
}
