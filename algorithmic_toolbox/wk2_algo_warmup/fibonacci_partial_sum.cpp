#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

int get_fibonacci_partial_slow(long long from, long long to) {

    if (to <=1)
	    return to;

    long long previous = 0;
    long long current  = 1;
    long long tmp = 1; // case where m = 0, default to (m+1)

    //S(m->n) = F(n+2) - F (m+1)
    for (long long i = 0; i < (to + 2 - 1); ++i) {

        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%10;

	if (i== (from+1-2)) //index m+1
		tmp = current;
    }

    int a = (current-tmp);

    return a >= 0 ? a : (10 + a) ;
}

int get_fib_partial_fast(long long from, long long to, vector <int> &debug){

   long long T = 0;
   if (to <=1) return to;
   long long previous = 0;
   long long current  = 1;

   while(true){
   	if(T!=0 && previous==0 && current ==1){
		break;
	}else{
	        long long tmp_previous = previous;
        	previous = current;
        	current = (tmp_previous + current)%10;
		T++;
	}
   }
   debug.push_back(T);
   debug.push_back(from%T);
   debug.push_back(to%T);

   //long long min = ( from%T <= to%T ? from%T : to%T);
   long long max =  ( from%T <= to%T ? to%T : (to%T + T)); 

   return get_fibonacci_partial_slow( from%T, max);

}


int main() {
    long long from, to;
    vector <int> db;
    std::cin >> from >> to;
    std::cout << get_fib_partial_fast(from, to, db) << '\n';
    //std::cout<< db[0] << " " << db[1] <<" " << db[2];
}
