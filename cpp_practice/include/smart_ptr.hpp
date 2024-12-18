#ifndef CPP_PRACTCE_INCLUDE_SMART_PTR_HPP
#define CPP_PRACTCE_INCLUDE_SMART_PTR_HPP

#include <memory>
#include <iostream>

namespace smart_ptr
{
    enum Gender
    {
        man = 0,
        woman = 1
    };

    class Person
    {
    public:
        Person() {}
        Person(double h, Gender g, std::size_t a) : height(h), gender(g), age(a) {}

        void GetInfo()
        {
            std::cout << "height:" << this->height << "\n"
                      << "gender:" << this->gender << "\n"
                      << "age:" << this->age << "\n";
        }
        ~Person() = default;

    private:
        double height;
        Gender gender;
        std::size_t age;
    };

    /**
     * @brief for test in main.cpp
     *
     */
    void Test1()
    {
        std::shared_ptr<Person> person = std::make_shared<Person>(180, man, 30);
        std::weak_ptr<Person> weak_ptr = person;

        std::cout << "person use_count:" << weak_ptr.use_count() << "\n";
        std::shared_ptr temp_ptr = weak_ptr.lock();

        std::cout << "person use_count:" << weak_ptr.use_count() << "\n";
        temp_ptr->GetInfo();
        std::cout << "person use_count:" << weak_ptr.use_count() << "\n";
    }

    void Test2()
    {
        std::unique_ptr<Person> person = std::make_unique<Person>(180, man, 30);
        person->GetInfo();
    }

} // namespace smart_ptr

#endif // CPP_PRACTCE_INCLUDE_SMART_PTR_HPP