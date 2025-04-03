#pragma once

#include <stdexcept>
#include <QDebug>
#include <iostream>
#include <sstream>

#define CHECK(expr, errMsg) \
    do { \
        if (!static_cast<bool>(expr)) [[unlikely]] { \
            std::ostringstream oss; \
            oss << "Check failed at " << __FILE__ << ": " << __LINE__ << ": " << errMsg; \
            std::cerr << oss.str() << std::endl;                \
            qDebug() << oss.str();                \
            throw std::runtime_error(oss.str()); \
        } \
    } while (false)
