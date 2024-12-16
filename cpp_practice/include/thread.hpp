#ifndef CPP_PRACTICE_THREAD_HPP
#define CPP_PRACTICE_THREAD_HPP

#include <iostream>

#include <thread>
#include <opencv4/opencv.hpp>

namespace thread
{
    void Get_parameters()
    {
        cv::FileStorage fs("../data/data.xml",cv::FileStorage::READ);
        if(!fs.isOpened())
        {
            std::cout << "Failed to open file" << "\n";
        }
        else
        {
            std::cout << "File opened successfully" << "\n";
        }
    }

    void Test1()
    {
        std::thread t([]()
                      { std::cout << "Hello from thread!" << "\n"; });
        t.join();
    }
}

#endif // CPP_PRACTICE_THREAD_HPP