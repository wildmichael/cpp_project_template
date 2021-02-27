#include <myproject/hello.hpp>

#include <iostream>

int main(int argc, char** argv)
{
    myproject::hello(std::cout, "Foo");
    std::cout << "My version is: " << MYPROJECT_VERSION_STRING << "\n";
}
