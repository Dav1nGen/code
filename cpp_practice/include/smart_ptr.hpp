#pragma once

#include <iostream>
#include <memory>

namespace smart_ptr {
enum Gender { man = 0, woman = 1 };

class Person {
public:
  Person() {}
  Person(double h, Gender g, std::size_t a) : height(h), gender(g), age(a) {}

  void GetInfo() {
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

void TestSharedPtr() {
  std::shared_ptr<Person> person = std::make_shared<Person>(180, man, 30);
  std::weak_ptr<Person> weak_ptr = person;

  std::cout << "person use_count:" << weak_ptr.use_count() << "\n";
  std::shared_ptr temp_ptr = weak_ptr.lock();

  std::cout << "person use_count:" << weak_ptr.use_count() << "\n";
  temp_ptr->GetInfo();
  std::cout << "person use_count:" << weak_ptr.use_count() << "\n";
}

void TestUniquePtr() {
  std::unique_ptr<Person> person1 = std::make_unique<Person>(180, man, 30);
  person1->GetInfo();

  // 转移person1的资源的所有权给person2
  std::unique_ptr<Person> person2 = std::move(person1);
  person2->GetInfo();
}

} // namespace smart_ptr
