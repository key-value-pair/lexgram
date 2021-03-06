#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class MemAllocException : std::exception {
public:
    const char* what() const noexcept override {
        return "memory allocated failed!";
    }
};

class NotFoundItemException : std::exception {
public:
    const char* what() const noexcept override {
        return "not found item!";
    }
};

class InvalidDataException : std::exception {
public:
    const char* what() const noexcept override {
        return "invalid data!";
    }
};

class InvalidRegExpException : std::exception {
public:
    const char* what() const noexcept override {
        return "invalid regular express!";
    }
};

#endif
