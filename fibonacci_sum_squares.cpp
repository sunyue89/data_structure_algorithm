#include <iostream>

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}
int fib_sum_sq_huge_slow(long long n){

    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    //S^2(n) = F(n)*F(n+1)
    for (long long i = 0; i < n + 1 - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%10;
    }

    return (current*previous)%10;

}

int fib_sum_sq_huge_fast(long long n){

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
        	current = (tmp_previous + current)%10;
		T++;
	}
   }
   return fib_sum_sq_huge_slow(n%T);

}
int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fib_sum_sq_huge_fast(n);
}
