#include "qh_string.h"

#include <string.h>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : data_(new char[1]), len_(0)
    {
        data_[0] = '\0';
    }

    string::string( const char* s )
        : data_(new char[strlen(s)+1]), len_(strlen(s))
    {
        strcpy(data_, s);
    }

    string::string( const char* s, size_t len )
    :data_(new char[len+1]), len_(len)
    {
        strncpy(data_, s, len);
    }

    string::string( const string& rhs )
    :data_(NULL), len_(0)
    {
        *this = rhs;
        len_ = rhs.size();
    }

    string& string::operator=( const string& rhs )
    {
        if(this == &rhs)
            return  *this;
        delete[] data_;
        data_ = new char[rhs.size()+1];
        strcpy(data_, rhs.data_);
        return *this;
    }

    string::~string()
    {
        if(data_ != NULL){
            delete[] data_;
            data_ = NULL;
            len_ = 0;
        }
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        char* temp = new char[len_];
        int i=0;
        for(; i<len_;i++)
            temp[i] = data_[i];
        return temp;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char* string::operator[]( size_t index )
    {
        if(index > len_-1 || index<0)
            return NULL;
        return &data_[index];
    }
}
