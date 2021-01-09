#ifndef TOKEN_H
#define TOKEN_H

#include <cstring>
#include <cstdlib>

#include "Exception.h"

class Token {
public:
    Token() = default;
    Token(char* data): data_(data) {}
    Token(char* data, size_t position, size_t length):
        data_(data), position_(position), length_(length) {}

    ~Token() {
        if (c_str_) {
            free(c_str_);
        }
    }
    
    size_t getLength() {
        return length_;
    }

    size_t getPosition() {
        return position_;
    }

    char* getCString() {
        if (c_str_ == nullptr) {
            c_str_ = (char *)malloc(length_ + 1);
            if (c_str_ == nullptr) {
                throw MemAllocException();
            }
        }

        memcpy(c_str_, data_ + position_, length_);
        c_str_[length_] = 0;
        
        return c_str_;
    }
        
private:
    size_t length_ = 0;
    size_t position_ = -1;
    char* c_str_ = nullptr;
    char* data_ = nullptr;
};

#endif
