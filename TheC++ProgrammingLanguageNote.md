- placement new
- {} initializer and constructor
- initializer_list
- member initalization
- volatile
- self-assignment
    This is especially important when your class does its own memory allocation
- slicing
    the copies only contain the base part of derived class object which is caused by invoking the base copy constructor instead of the derived one.
- what does default move operations do?
- overload solutions, interpretation and conversions
    which function will be invoked when there are not just one matched overload functions?  
    when will the implict conversions happen?  
- why special operator function must be a non-static member function?
    because those usually take the object as the lvalue, and it couldn't all be static for objects from that class.
- operator overloading for prefix and postfix
    ```cpp
    // increment_and_decrement2.cpp
    class Int {
    public:
        Int(int i) : _i{i} {};
        Int& operator++();      // Prefix increment operator.
        Int operator++(int n);  // Postfix increment operator.
        int make_int() { return _i; }

    private:
        int _i;
    };

    Int& Int::operator++() {
        ++_i;
        return *this;
    }

    Int Int::operator++(int n) {
        Int result = *this;
        if (n != 0)  // Handle case where an argument is passed.
            _i += n;
        else
            _i++;  // Handle case where no argument is passed.
        return result;
    }

    Int operator+(Int i, Int j) { return Int{i.make_int() + j.make_int()}; }

    int main() {
        Int i{0};
        i.operator++(25);  // Increment by 25.
    }
    ```
- variadic template
- const and non-const function
    only const member function can be called when declared as const object
    ```cpp
    class Foo {
    public:
        //invoke when "this" is a const object
        void foo() const { std::cout << "const\n"; }
        //invoke when "this" isn't a const object
        void foo() { std::cout << "non-const\n"; }
    };
    ```
- the standard-library memcpy() should be used only where there are no objects with constructors or destructors in the copied memory
- is std::copy capable of copy non-POD?
- use memcpy to copy memory for the same type, would it work?
- friend functions and classes
    friend is one-direction, class A declares class B as friend only makes class B capable of access private member of class A, but not vice versa.
- independently of which base class (interface) is used to access an object, we always get the same function when we use the virtual fucntion call mechanism
    ```cpp
    class Foo {
    private:
        int a{0};

    public:
        void print() { cout << "foo" << endl; }
        virtual void print_virtual() { cout << "foo" << endl; }
    };

    class Bar : public Foo {
    public:
        void print() { cout << "bar" << endl; }
        void print_virtual() { cout << "bar" << endl; }
    };

    int main(int argc, char const *argv[]) {
        Bar bar;
        Foo *foo = &bar;
        foo->print();//foo
        foo->print_virtual();//bar
        return 0;
    }
    ```
- public, protected and private inheritance
    - public inheritance makes public members of the base class public in the derived class, and the protected members of the base class remain protected in the derived class.
    - protected inheritance makes the public and protected members of the base class protected in the derived class.
    - private inheritance makes the public and protected members of the base class private in the derived class.
- pointer to member type
- abstract class as interfaces 
- virtual base is an option to resolve the need of sharing data in class hierachy but try not to use it
- the constructor of a base class will not be inherited to a derived class
- undefined reference to XXX may comes because template function defined in *.cpp
    template functions must be defined in header files unless you explict write `template void foo<int>();`, yes ,explict write every pattern that is used... 
- template is a "way" of defining container easily
- enum, enumerator, enumeration?
- virtual table
- how to make class usable in ranged-for