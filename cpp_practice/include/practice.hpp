#pragma once

#include <utility>
#include <iostream>

namespace practice {

class Class
{
public:
    Class()=default;
    ~Class()=default;

    int a=1;
    int b=2;
};

void Test1()
{
    Class c1;
    Class* ptr=&c1;
    std::cout<<"c1 address:"<<&ptr<<"\n";
    Class c2(std::move(c1));
    ptr=&c2;
    std::cout<<"c2 address:"<<&ptr<<"\n";
}

}  // namespace practice
