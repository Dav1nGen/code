/**
 * @file thread_pool.hpp
 * @author Dav1nGen (davicheng1114@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-12-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

namespace thread_pool {

/**
 * @brief 任务类
 *
 */
class Task
{
public:
    using TaskFunction = std::function<void()>;

    Task(TaskFunction&& func) : function_(std::move(func)) {}
    ~Task() = default;

    void Execute()
    {
        function_();  // 执行任务
    }

private:
    std::function<void()> function_;
};

/**
 * @brief 任务队列
 *
 */
class TaskQueue
{
public:
    TaskQueue()  = default;
    ~TaskQueue() = default;
    std::condition_variable task_queue_cv;
    void PushTask(std::shared_ptr<Task> task)
    {
        std::lock_guard<std::mutex> lock(task_queue_mutex_);
        task_queue_.push(std::move(task));
        task_queue_cv.notify_one();  // 通知线程池有新的任务
    }

    std::shared_ptr<Task> PopTask()
    {
        std::unique_lock<std::mutex> lock(task_queue_mutex_);
        task_queue_cv.wait(lock, [this]() { return !task_queue_.empty(); });
        std::shared_ptr<Task> task = task_queue_.front();
        task_queue_.pop();
        return task;
    }

private:
    std::queue<std::shared_ptr<Task>> task_queue_;
    std::mutex task_queue_mutex_;
};

/**
 * @brief 线程池类
 *
 */
class ThreadPool
{
public:
    ThreadPool(size_t threads_num) : is_running_(true)
    {
        // 创建线程池中的线程
        for (size_t i = 0; i < threads_num; ++i)
        {
            threads_.emplace_back(&ThreadPool::Worker, this);
        }
    }

    ~ThreadPool()
    {
        // 停止线程池并等待所有线程结束
        is_running_ = false;
        taskQueue_.task_queue_cv.notify_all();  // 唤醒所有线程
        for (auto& t : threads_)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
    }

    // 提交任务到线程池
    void Submit(std::shared_ptr<Task> task) { taskQueue_.PushTask(task); }

private:
    // 工作线程执行函数
    void Worker()
    {
        while (is_running_)
        {
            std::shared_ptr<Task> task = taskQueue_.PopTask();
            if (task)
            {
                task->Execute();
            }
        }
    }

    std::vector<std::thread> threads_;  // 工作线程列表
    TaskQueue taskQueue_;               // 任务队列
    std::atomic<bool> is_running_;      // 线程池是否处于运行状态
};

void TestThreadPool()
{
    ThreadPool pool(4);
    for (int i = 0; i < 10; ++i)
    {
        pool.Submit(std::make_shared<Task>(
            [i]() { std::cout << "Task " << i << "\n"; }));
    }
}

}  // namespace thread_pool