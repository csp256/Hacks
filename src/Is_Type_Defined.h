#include <iostream>
#include <type_traits>
#include <utility>

template<typename T, typename = void>
constexpr bool is_defined = false;

template<typename T>
constexpr bool is_defined<T, decltype(typeid(T), void())> = true;

struct defined { };
struct forward_declared;

template <typename T>
struct Foo {
    T x;
};

int main()
{
    std::cout << std::boolalpha // TIL: std::boolalpha!
              << is_defined<defined> << std::endl // true
              << is_defined<forward_declared> << std::endl // false
              // << is_defined<Foo> << std::endl // Does not compile!
              << is_defined<Foo<int> > << std::endl; // true
}
