#pragma once

#include <iostream>
#include <string>

// 时间类 用于获取当前时间
class Timestamp
{

public:
    Timestamp() : microSecondsSinceEpoch_(0) {}
    explicit Timestamp(int64_t microSecondsSinceEpoch);
    static Timestamp now();
    std::string toString() const;

    void swap(Timestamp& that)
    {
        std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
    }
    
private:
    int64_t microSecondsSinceEpoch_;
};
