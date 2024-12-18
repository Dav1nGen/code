#pragma once

#include <functional>
#include <iostream>
#include <thread>

namespace thread_pool {
class Task {
public:
  using TaskFunction = std::function<void()>;

  Task(TaskFunction &func) : function_(std::move(func)) {}

private:
  std::function<void()> function_;
};

class ThreadPool {};

class TaskQueue {};
} // namespace thread_pool