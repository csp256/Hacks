#include <iostream>
#include <vector>

/* 
    C++ 17 as written (may be  refactored to work with 14? replace decay_t with decay<>::value ?)
*/

#include <range/v3/all.hpp>

template <typename T>
auto indices(const T & x)
{
    return ranges::v3::view::ints(
        static_cast<typename 
            std::decay_t<T>::size_type //::size_type
        >(0)
    );
}

template <typename T>
auto zip(const T & x) { return ranges::v3::view::zip(x, indices(x)); }

auto main(int argc, char **argv) -> int
{
	std::vector<double> x = {1.0, 2.0, 3.0, 4.0};

	for(auto &&[elm, i]: zip(x)) {
		std::cout << elm << ' ' << i << std::endl;
	}
}
