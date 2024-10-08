#pragma once

#include "copyable.h"
#include "Timestamp.h"

#include <map>
#include <string>
#include <stdio.h>

using namespace std;

class HttpRequest : public copyable
{
public:
    enum Method  // http请求类型枚举
    {
        kInvalid,
        kGet,
        kPost,
        kHead,
        kPut,
        kDelete
    };
    enum Version // http版本
    {
        kUnknown,
        kHttp10,
        kHttp11
    };

    HttpRequest()
        : method_(kInvalid),
          version_(kUnknown)
    {
    }

    void setVersion(Version v)
    {
        version_ = v;
    }

    Version getVersion() const
    {
        return version_;
    }

    bool setMethod(const char *start, const char *end)
    {
        if(method_ == kInvalid)
        {
            string m(start, end);
            if (m == "GET")
            {
                method_ = kGet;
            }
            else if (m == "POST")
            {
                method_ = kPost;
            }
            else if (m == "HEAD")
            {
                method_ = kHead;
            }
            else if (m == "PUT")
            {
                method_ = kPut;
            }
            else if (m == "DELETE")
            {
                method_ = kDelete;
            }
            else
            {
                method_ = kInvalid;
            }
        }
        return method_ != kInvalid;
    }

    Method method() const
    {
        return method_;
    }

    const char *methodString() const
    {
        const char *result = "UNKNOWN";
        switch (method_)
        {
        case kGet:
            result = "GET";
            break;
        case kPost:
            result = "POST";
            break;
        case kHead:
            result = "HEAD";
            break;
        case kPut:
            result = "PUT";
            break;
        case kDelete:
            result = "DELETE";
            break;
        default:
            break;
        }
        return result;
    }

    void setPath(const char *start, const char *end)
    {
        path_.assign(start, end);
    }

    const string &path() const
    {
        return path_;
    }

    void setQuery(const char *start, const char *end)
    {
        query_.assign(start, end);
    }

    const string &query() const
    {
        return query_;
    }

    void setReceiveTime(Timestamp t)
    {
        receiveTime_ = t;
    }

    Timestamp receiveTime() const
    {
        return receiveTime_;
    }

    void addHeader(const char *start, const char *colon, const char *end) // HTTP 头部字段的开始、冒号位置和结束位置
    {
        string field(start, colon);
        ++colon;
        while (colon < end && isspace(*colon))
        {
            ++colon;
        }
        string value(colon, end);
        while (!value.empty() && isspace(value[value.size() - 1]))
        {
            value.resize(value.size() - 1);
        }
        headers_[field] = value;
    }

    string getHeader(const string &field) const
    {
        string result;
        std::map<string, string>::const_iterator it = headers_.find(field);
        if (it != headers_.end())
        {
            result = it->second;
        }
        return result;
    }

    const std::map<string, string> &headers() const
    {
        return headers_;
    }

    void swap(HttpRequest &that)
    {
        std::swap(method_, that.method_);
        std::swap(version_, that.version_);
        path_.swap(that.path_);
        query_.swap(that.query_);
        receiveTime_.swap(that.receiveTime_);
        headers_.swap(that.headers_);
    }

private:
    Method method_;     // 请求类型
    Version version_;   // http版本
    string path_;       // URL路径
    string query_;      // 查询文件内容
    Timestamp receiveTime_; // 请求时间戳
    std::map<string, string> headers_;  // 哈希查询
};
