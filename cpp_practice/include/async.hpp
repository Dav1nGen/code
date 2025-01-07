#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <atomic>

namespace async {

std::mutex mtx;
std::condition_variable cv;
std::queue<int> data_queue;
bool finished = false;

void Producer()
{
    for (int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> lock(mtx);
        data_queue.push(i);
        std::cout << "Produced: " << i << std::endl;
        cv.notify_one();  // 通知消费者
    }

    // 生产结束
    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    cv.notify_all();  // 通知所有等待的线程
}

void Consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !data_queue.empty() || finished; });
        while (!data_queue.empty())
        {
            int value = data_queue.front();
            data_queue.pop();
            std::cout << "Consumed: " << value << std::endl;
        }
        if (finished && data_queue.empty()) break;
    }
}

void Test1()
{
    std::thread t1(Producer);
    std::thread t2(Consumer);

    t1.join();
    t2.join();
}

//-------------------------------------------------------------------------//
std::atomic<int> ato=0;
std::mutex mtx2;
std::condition_variable cv2;
bool func1_trun=true;
void func1()
{
    for(int i=0;i<100;i++)
    {
        std::unique_lock<std::mutex> lock(mtx2);
        cv2.wait(lock,[]{return func1_trun;});
        ato=1;
        std::cout<<ato<<"\n";
        func1_trun=false;
        cv2.notify_one();
    }
    
}

void func2()
{
    for(int i=0;i<100;i++)
    {
        std::unique_lock<std::mutex> lock(mtx2);
        cv2.wait(lock,[]{return !func1_trun;});
        ato=2;
        std::cout<<ato<<"\n";
        func1_trun=true;
        cv2.notify_one();
    }
    
}

void Test2()
{
    std::thread t1([](){func1();});
    std::thread t2([](){func2();});

    t1.join();
    t2.join();
}

}  // namespace async
