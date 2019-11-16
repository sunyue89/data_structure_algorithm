#include <iostream>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long long get_fib_huge_slow(long long n, long long m){
	
    if (n <= 1) return n;
    
    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%m;
    }

    return current;


}

long long get_fib_huge_fast(long long n, long long m){
   long long T = 0;
   if (n <=1) return n;
   long long previous = 0;
   long long current  = 1;

   while(true){
   	if(T!=0 && previous==0 && current ==1){
		break;
	}else{
	        long long tmp_previous = previous;
        	previous = current;
        	current = (tmp_previous + current)%m;
		T++;
	}
   }
   return get_fib_huge_slow(n%T,m);

}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fib_huge_fast(n, m) << '\n';
}
