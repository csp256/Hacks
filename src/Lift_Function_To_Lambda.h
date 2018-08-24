// Note, this solves the issue in:
// https://ibob.github.io/blog/2018/08/18/a-bug-in-the-cpp-standard/

template <typename T>
auto lift(T c)
{
    return [c](auto ... args) 
    {
        return c(args...); 
    }; 
}
