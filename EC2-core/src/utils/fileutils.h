﻿#pragma once

#include <string>

namespace ec2 {

    static std::string read_file(const char* filepath)
    {
        FILE * file;
        errno_t err = fopen_s(&file, filepath, "rt");
        fseek(file, 0, SEEK_END);
        unsigned long length = ftell(file);
        char * data = new char[length + 1];
        memset(data, 0, length + 1);
        fseek(file, 0, SEEK_SET);
        fread(data, 1, length, file);
        fclose(file);

        std::string result(data);
        delete[] data;

        return result;
    }

    /*std::string read_file(const std::string& filepath) {
        std::ifstream ifs((filepath).c_str());
        std::string content(
            std::istreambuf_iterator<char>(ifs.rdbuf()),
            std::istreambuf_iterator<char>()
        );
        return content;
    }*/
}
