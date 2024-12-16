#ifndef CPP_PRACTICE_THREAD_HPP
#define CPP_PRACTICE_THREAD_HPP

#include <iostream>
#include <string>
#include <assert.h>

#include <thread>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/core/persistence.hpp>

namespace thread
{
    class FileReader
    {
    public:
        FileReader(std::string file_path) : _file_path(file_path)
        {
            cv::FileStorage file_storage(_file_path, cv::FileStorage::READ);
            assert(file_storage.isOpened());
            std::cout << "File opened successfully" << "\n";

            this->fs = file_storage;
        }
        cv::FileStorage fs;

    private:
        std::string _file_path;
    };

    void Test1()
    {
        int width;
        int height;
        int fps;
        std::thread t([]()
                      { std::cout << "Hello from thread!" << "\n"; });
        t.join();
        FileReader fr("../../../../config/config.yaml");
        fr.fs["width"] >> width;
        fr.fs["height"] >> height;
        fr.fs["fps"] >> fps;

        std::cout << "width: " << width << "\n"
                  << "height: " << height << "\n"
                  << "fps: " << fps << "\n";
    }
}

#endif // CPP_PRACTICE_THREAD_HPP