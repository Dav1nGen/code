#ifndef CPP_PRACTICE_INCLUDE_FILE_STORAGE_HPP
#define CPP_PRACTICE_INCLUDE_FILE_STORAGE_HPP

#include <iostream>
#include <string>
#include <assert.h>

#include <thread>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/core/persistence.hpp>

namespace file_storage
{
    class FileReader
    {
    public:
        FileReader(std::string file_path) : _file_path(file_path)
        {
            cv::FileStorage file_storage(_file_path, cv::FileStorage::READ);

            if (!file_storage.isOpened())
            {
                std::string error_msg = "File \"" + file_path + "\" open failed.";
                std::cerr << error_msg << std::endl;
                throw std::runtime_error(error_msg);
            }

            this->fs = file_storage;
        }
        ~FileReader()
        {
            this->fs.release();
        }

        template <typename T>
        T Read(std::string key)
        {
            const char* cstr = key.c_str();
            if (fs[cstr].empty())
            {
                throw std::runtime_error("Key: \"" + key + "\" not found in the file.");
            }
            T value;
            fs[cstr] >> value;
            return value;
        }

    private:
        std::string _file_path;
        cv::FileStorage fs;
    };

    class FileWriter
    {
    public:
        FileWriter(std::string file_path) : _file_path(file_path)
        {
            cv::FileStorage file_storage(_file_path, cv::FileStorage::WRITE);

            if (!file_storage.isOpened())
            {
                std::string error_msg = "File \"" + file_path + "\" open failed.";
                std::cerr << error_msg << std::endl;
                throw std::runtime_error(error_msg);
            }

            this->fs = file_storage;
        }
        ~FileWriter()
        {
            this->fs.release();
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

        {
            FileReader fr("../../../../config/config.yaml");
            width = fr.Read<int>(std::string("width"));
            height = fr.Read<int>(std::string("height"));
            fps = fr.Read<int>(std::string("fps"));
        }

        std::cout << "width: " << width << "\n"
                  << "height: " << height << "\n"
                  << "fps: " << fps << "\n";
        {
            FileWriter fw("../../../../config/config.yaml");
            fw.fs << "width" << 100;
            fw.fs << "height" << 200;
            fw.fs << "fps" << 300;
        }

        {
            FileReader fr("../../../../config/config.yaml");
            width = fr.Read<int>(std::string("width"));
            height = fr.Read<int>(std::string("height"));
            fps = fr.Read<int>(std::string("fps"));
        }

        std::cout << "width: " << width << "\n"
                  << "height: " << height << "\n"
                  << "fps: " << fps << "\n";
    }
}

#endif // CPP_PRACTICE_INCLUDE_FILE_STORAGE_HPP