#include <algorithm>  
#include <future>     
#include <iterator>   
#include <vector>
#include <iostream>   

template <typename Iterator, typename Function>
void parallel_for_each(Iterator begin, Iterator end, Function func, size_t min_block_size = 25) {
    
    auto length = std::distance(begin, end);

   
    if (length <= static_cast<long>(min_block_size)) {
        std::for_each(begin, end, func); 
    }
    else {
        
        Iterator mid = begin;
        std::advance(mid, length / 2);

       
        auto future = std::async(std::launch::async,
            [&]() { parallel_for_each(begin, mid, func, min_block_size); });

      
        parallel_for_each(mid, end, func, min_block_size);

       
        future.get();
    }
}

int main() {
    std::vector<int> data(1000, 1); 

  
    parallel_for_each(data.begin(), data.end(), [](int& n) { ++n; });

   
    for (const auto& n : data) {
        std::cout << n << " "; 
    }

    return 0;
}