#include <chrono>
  
#define PROFILE(_FUNC) do {                                                      \
  using namespace std::chrono;                                                   \
  const high_resolution_clock::time_point start = high_resolution_clock::now();  \
  _FUNC();                                                                       \
  const high_resolution_clock::time_point end = high_resolution_clock::now();    \
  const nanoseconds NS = (end - start);                                          \
  std::cout << #_FUNC << " " << NS.count() / 1000. / 1000. << std::endl;         \
} while(0) // ;

void foo()
{
  auto bar = []() -> void 
  {
    /* ... */
  };
  
  PROFILE(bar);
}


#undef PROFILE
