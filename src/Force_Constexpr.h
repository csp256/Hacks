// https://quuxplusone.github.io/blog/2018/08/07/force-constexpr/

#define FORCE_CONSTEXPR(expr) [&]() \
    { constexpr auto x = (expr); return x; }()
    
// For global scope with clang use:

#define GFORCE_CONSTEXPR(expr) []() \
    { constexpr auto x = (expr); return x; }()

int global = GFORCE_CONSTEXPR(constexpr_sqrt(42.0));
