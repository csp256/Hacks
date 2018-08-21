// CRTP := Curiously Recurring Template Pattern

// Call subclass member function from superclass member function
{
    template <class Derived>
    class SuperClass
    {    
        void Foo() {
            // some SuperClass specific code
            static_cast<Derived*>(this)->Bar();
            // Depending on context, might need to do:
            // static_cast<const Derived * const>(this)->Bar();
        }
    }

    class BaseClass : public SuperClass<SubClass>
    {
        void Bar(T&) {
            // some SubClass related code
        }
    }
}
