template<typename T> class reverse_adapter { 
    public: 
        reverse_adapter(T& c) : c(c) { } 
        typename T::reverse_iterator begin() { return c.rbegin(); } 
        typename T::reverse_iterator end() { return c.rend(); } 
    private: 
        T& c; 
}; 

template<typename T> 
reverse_adapter<T> reverse_iteration(T &c) { return reverse_adapter<T>(c); } 

//

std::vector<int> v {1, 2, 3}; 
for (auto & i : reverse_iteration(a)) {
    cout << i; // prints 321
}
