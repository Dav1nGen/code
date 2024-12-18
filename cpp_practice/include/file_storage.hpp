#pragma once

// C++ standard library header file
#include <assert.h>

#include <iostream>
#include <string>

// Third-party library headers
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/core/persistence.hpp>
#include <opencv4/opencv2/opencv.hpp>

// Custom header files
// none

namespace file_storage {
class FileReader
{
public:
    FileReader(std::string file_path) : file_path_(file_path)
    {
        cv::FileStorage file_storage(file_path_, cv::FileStorage::READ);

        if (!file_storage.isOpened())
        {
            std::string error_msg = "File \"" + file_path + "\" open failed.";
            std::cerr << error_msg << std::endl;
            throw std::runtime_error(error_msg);
        }

        this->fs_ = file_storage;
    }
    ~FileReader() { this->fs_.release(); }

    template <typename T>
    T Read(std::string key)
    {
        const char *cstr = key.c_str();
        if (fs_[cstr].empty())
        {
            throw std::runtime_error("Key: \"" + key +
                                     "\" not found in the file.");
        }
        T value;
        fs_[cstr] >> value;
        return value;
    }

private:
    const std::string file_path_;
    cv::FileStorage fs_;
};

class FileWriter
{
public:
    FileWriter(std::string file_path) : file_path_(file_path)
    {
        cv::FileStorage file_storage(file_path_, cv::FileStorage::WRITE);

        if (!file_storage.isOpened())
        {
            std::string error_msg = "File \"" + file_path + "\" open failed.";
            std::cerr << error_msg << std::endl;
            throw std::runtime_error(error_msg);
        }

        this->fs = file_storage;
    }
    ~FileWriter() { this->fs.release(); }
    cv::FileStorage fs;

private:
    std::string file_path_;
};

void TestFileReaderWriter()
{
    int width;
    int height;
    int fps;

    {
        FileReader fr("../../../../config/config.yaml");
        width  = fr.Read<int>(std::string("width"));
        height = fr.Read<int>(std::string("height"));
        fps    = fr.Read<int>(std::string("fps"));
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
        width  = fr.Read<int>(std::string("width"));
        height = fr.Read<int>(std::string("height"));
        fps    = fr.Read<int>(std::string("fps"));
    }

    std::cout << "width: " << width << "\n"
              << "height: " << height << "\n"
              << "fps: " << fps << "\n";
}
}  // namespace file_storage