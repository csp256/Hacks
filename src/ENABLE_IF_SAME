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
