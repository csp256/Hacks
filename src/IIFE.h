// IIFE := Immediately Invoked Function Expression

    // Many uses, but I like this one:

const int x = [&] {
    if (b1)
        return b2 ? Foo(y) : 0;
    else
        return 2 * y;
}();

    // Alternative:

int x_;
if (b1) 
    x_ = b2 ? Foo(y) : 0;
else
    x_ = 2 * y;
const int x = x_;
// x_ unavoidably stays in scope!

    // Alternative 

const int x = b1 ? (b2 ? Foo(y) : 0) : (2 * y);
// Nested ternary operators are hard to read and not scalable.
