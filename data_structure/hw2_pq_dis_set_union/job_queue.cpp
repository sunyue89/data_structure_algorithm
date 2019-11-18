#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iterator>

using namespace std;
using std::vector;
using std::cin;
using std::cout;
using std::pair;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;
  //priority queue that contains the thread and start time pair
  //the length of pq will be the same as jobs
  
  class QueueRule {
	  public:bool operator()(pair<int, long long>&p1, pair<int, long long>&p2){
			if(p1.second == p2.second){
				return (p1.first > p2.first);
			}else{ return (p1.second > p2.second);}
		 } 
  };
  priority_queue<pair<int, long long>, vector<pair<int, long long>>, QueueRule> job_N_st_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    /*
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }*/   
	assigned_workers_.resize(jobs_.size());
	start_times_.resize(jobs_.size());
	//job_N_st_.resize(jobs_.size());

	for (int i=0; i<num_workers_; ++i){
		//if thread number is less than jobs, keep scheduling
		//else, no need to push, everything will be scheduled
		if( i <= jobs_.size() - 1 ){
			job_N_st_.push(make_pair(i,0));
		}else{
			break;
		}
	}

	for (int i =0; i<jobs_.size(); ++i){
		pair<int, long long> Current_Job = job_N_st_.top();
		assigned_workers_[i] = Current_Job.first;
		start_times_[i] = Current_Job.second;
		job_N_st_.pop();
		job_N_st_.push(make_pair(Current_Job.first, Current_Job.second+jobs_[i]));
	}


  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
