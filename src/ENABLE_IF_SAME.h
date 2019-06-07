template <class T, class ... args>
struct is_any : std::disjunction<std::is_same<T, args>...> {};

#define ENABLE_IF(ARG_1, ...)\
    typename std::enable_if_t<is_any<ARG_1, __VA_ARGS__>::value> * = nullptr

// Usage
template <typename T, ENABLE_IF(T, float, double)>
void f(T x) {}

f(3); // ok
f(3.14); // not-ok

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
