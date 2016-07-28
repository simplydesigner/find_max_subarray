#include <iostream>
#include <vector>
#include <algorithm>

struct result {
    unsigned int begin_index;
    unsigned int end_index;
    int summary;
};

auto print_result(const result & result)
{
    std::cout << "[" << result.begin_index << ", " << result.end_index << "]: " << result.summary << std::endl;
}

auto find_max_crossing_subarray(const std::vector<int> & array, unsigned int begin_index, unsigned int middle_index, unsigned int end_index) -> result
{
    unsigned int left_index = middle_index - 1;
    int left_summary = array[ middle_index - 1 ];
    int summary = left_summary;
    for ( unsigned int index = middle_index - 1; index > begin_index; --index ) {
        auto real_index = index - 1;
        summary += array[ real_index ];
        if ( summary > left_summary ) {
            left_summary = summary;
            left_index = real_index;
        }
    }
    
    
    unsigned int right_index = middle_index;
    int right_summary = array[ middle_index ];
    summary = right_summary;
    for ( unsigned int index = middle_index + 1; index < end_index; ++index ) {
        summary += array[ index ];
        if ( summary > right_summary ) {
            right_summary = summary;
            right_index = index;
        }
    }
    
    return {left_index, right_index, left_summary + right_summary};
}

auto ceil(int a, int b)
{
    return (a / b) + ((a % b) > 0);
}

auto floor(int a, int b)
{
    return (a / b) - ((a % b) > 0);
}

auto find_max_subarray(const std::vector<int> & array, unsigned int begin_index, unsigned int end_index) -> result
{
    if ( begin_index + 1 == end_index ) {
        return {begin_index, end_index, array[ begin_index ]};
    }
    
    unsigned int middle_index = ceil(begin_index + end_index, 2);
    
    auto left_result = find_max_subarray(array, begin_index, middle_index);
    auto right_result = find_max_subarray(array, middle_index, end_index);
    auto middle_result = find_max_crossing_subarray(array, begin_index, middle_index, end_index);
    
    if ( left_result.summary > right_result.summary && left_result.summary > middle_result.summary ) {
        return left_result;
    }
    else
    if ( right_result.summary > middle_result.summary ) {
        return right_result;
    }
    else {
        return middle_result;
    }
}

auto print_array(const std::vector<int> & array)
{
    std::ostream_iterator<int> output_iterator(std::cout, " ");
    std::copy(array.begin(), array.end(), output_iterator);
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {

    std::vector<int> array = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    
    print_array(array);
    
    auto result = find_max_subarray(array, 0, array.size());
    print_result(result);
    
    
    return 0;
}
