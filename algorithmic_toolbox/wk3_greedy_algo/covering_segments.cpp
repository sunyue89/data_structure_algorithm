#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

bool sort_oprt (Segment a1, Segment a2){

	return (a1.start < a2.start);
}

bool intersect (Segment a1, Segment a2){
	return (a2.start <= a1.end); 
}

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;

  sort(segments.begin(),segments.end(),sort_oprt);

  Segment roll = segments[0];
  //points.push_back(roll.end);

  for (int i = 1; i<segments.size(); i++){
	
  	if(intersect(roll,segments[i])){
		roll = {segments[i].start, std::min(roll.end,segments[i].end)};
	}	
	else{
		points.push_back(roll.end);
		roll = segments[i];
	}
  }
  points.push_back(roll.end);
  //write your code here
  /*
  for (size_t i = 0; i < segments.size(); ++i) {
    points.push_back(segments[i].start);
    points.push_back(segments[i].end);
  }
  */
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
