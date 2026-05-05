#pragma once

#include <iostream>
#include <vector>



template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]" << std::endl;
    return os;
}


template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &mat)
{
    if (mat.empty())
    {
        os << "[]";
        return os;
    }

    os << "[\n"; // 开头换行
    for (size_t i = 0; i < mat.size(); ++i)
    {
        os << "  " << mat[i]; // 每行前加两个空格缩进
        if (i != mat.size() - 1)
        {
            os << ",";
        }
        os << "\n"; // 每行结束后换行
    }
    os << "]"<<std::endl;
    return os;
}