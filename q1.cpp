// #include <iostream>

// class Foo
// {
// public:
//     Foo() { baz(); }
//     virtual void baz() { std::cout << "Foo::baz()" << std::endl; }
// };

// class Bar : public Foo
// {
// public:
//     Bar() : Foo() { baz(); } // Call the default constructor of Foo
//     Bar(int x) { baz(); }
//     virtual void baz() { std::cout << "Bar::baz()" << std::endl; }
// };

// int main()
// {
//     Foo *pFoo = new Bar(5);
//     delete pFoo;
//     return 0;
// }


// /* the output is "Foo:baz()"*/