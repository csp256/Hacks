/*

    Enables a function only if each of a variadic number of types (or each of a tuple)
    is contained within a whitelist (stored as a tuple of types).

*/

#include <type_traits>
#include <tuple>

using whitelist = std::tuple<int, bool>;

//

template <typename T, class Tuple>
struct is_any;

template <class T, class ... U>
struct is_any<T, std::tuple<U ...>> 
    : std::disjunction< std::is_same<T, U> ... > {};

//

template <class T, class U>
struct all_in_whitelist;

template <class ... T, class U>
struct all_in_whitelist<std::tuple<T ...>, U> 
    : std::conjunction< is_any<T, U> ... > {};

//

template <typename T>
using enable_if_ = std::enable_if_t< T::value >;

template<class U, class ... T >
using enable_if_whitelisted = enable_if_< all_in_whitelist<std::tuple<T ...>, U> >;

//

#define UNPACK( ... ) __VA_ARGS__

#define ENABLE_IF_IMPL( ARG ) typename = enable_if_whitelisted< UNPACK ARG > 

#define ENABLE_IF( ... ) ENABLE_IF_IMPL((__VA_ARGS__))

//

template <typename ... T, ENABLE_IF(whitelist, T ...)>
void f(std::tuple<T ...> t)
{}

template <typename T, ENABLE_IF(whitelist, T)>
void g(T  t)
{}

//

int main()
{
    auto x = std::tuple{1, true};
    f(x);

    auto y = std::tuple{1, true, 3.14};
    // f(y);

    g(3);
    // g(3.14);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#include <type_traits>

template <class T, class ... Args>
struct is_any : std::disjunction<std::is_same<T, Args> ...> {};

template <class T, class ... Args>
struct are_all : std::conjunction<std::is_same<T, Args> ...> {};

template <typename Condition>
using EnableIf = std::enable_if_t<Condition::value>;

#define UNPACK_MACRO( ... ) __VA_ARGS__
// Black magic
#define ENABLE_IF_IMPL( ARG ) typename = EnableIf< UNPACK_MACRO ARG > 

#define ENABLE_IF( ... ) ENABLE_IF_IMPL((__VA_ARGS__))

// Usage
template <typename T, ENABLE_IF(is_any<T, float, double>)>
void f(T x) {}

f(3); // not-ok
f(3.14); // ok


/*
newst / best
--------
older
*/

template <class T, class ... args>
struct is_any : std::disjunction<std::is_same<T, args>...> {};

#define ENABLE_IF(ARG_1, ...)\
    typename std::enable_if_t<is_any<ARG_1, __VA_ARGS__>::value> * = nullptr

// Usage
template <typename T, ENABLE_IF(T, float, double)>
void f(T x) {}

f(3); // not-ok
f(3.14); // ok

/*
new
-----------
old
*/

#define ENABLE_IF_SAME(ARG_1, ARG_2) typename std::enable_if< std::is_same<ARG_1, ARG_2>::value>::type * = nullptr

// Usage
template <typename T, typename U, ENABLE_IF_SAME(U, double)>
int Foo(const T & x, const U & y) 
{
  return 1;
}

template <typename T, typename U, ENABLE_IF_SAME(U, size_t)>
int Foo(const T & x, const U & y) 
{
  return 2;
}

template <typename T, typename U, ENABLE_IF_SAME(U, T)>
int Foo(const T & x, const U & y) 
{
  return 3;
}

Foo<int, double>(); // 1
Foo<int, size_t>(); // 2
Foo<int, int>();    // 3
