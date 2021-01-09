#ifndef EXCEPTION_H
#define EXCEPTION_H

class MemAllocException : std::exception {
public:
    const char* what() const noexcept override {
        return "memory allocated failed!";
    }
};

#endif
