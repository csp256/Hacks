
{
    struct Foo {};
    typedef Foo Bar;
    std::is_same<Foo, Bar>::value; // true
}

/*
    What if we wanted to create a new, different type which was elsewise-identical to Foo?

    This feature, opaque/strong typedef, is not natively possible in C++.

    A workaround is available using Tagged Dispatch. 
*/

{
    template <typename T, typename Tag>
    struct Foo {
        T data;
        void Name() { return Tag::Name(); }
    }

    #define STR(X) #X
    #define OPAQUE_TYPEDEF(EXTANT_TYPE, NEW_TYPE, ARG_1) \
        struct NEW_TYPE##_UNIQUE_TAG { \
            static constexpr char Name[] = STR(NAME); \
        }; \
        typedef EXTANT_TYPE##<ARG_1, NEW_TYPE##_UNIQUE_TAG>

    OPAQUE_TYPEDEF(Foo, Bar1, double);
    OPAQUE_TYPEDEF(Foo, Bar2, double);

    #undef OPAQUE_TYPEDEF
    #undef STR

    std::is_same<Foo, Bar1>::value; // false
    std::is_same<Foo, Bar2>::value; // false
    std::is_same<Bar1, Bar2>::value; // false

/*
    Note this also provides easy reflection:
*/

    std::cout << Bar1.Name() << std::endl; // Bar1
    std::cout << Bar2.Name() << std::endl; // Bar2
}
