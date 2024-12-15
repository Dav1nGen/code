#include <iostream>
#include <BS_thread_pool.hpp>
#include <future>

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

std::vector<int> find_primes_in_range(int start, int end) {
    std::vector<int> primes;
    for (int i = start; i <= end; ++i) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}

int main(int argc, char** argv) {
    BS::thread_pool pool;
    std::future<std::vector<int>> my_future = pool.submit_task(
        []{find_primes_in_range(1, 1000000);} 
    );
    return 0;
}
