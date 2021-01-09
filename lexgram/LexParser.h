#ifndef LEXPARSER_H
#define LEXPARSER_H

#include <string>
#include <vector>

#include "Token.h"

class LexParser {
public:
    LexParser() = default;
    ~LexParser() = default;

    void setData(char* data) {
        data_ = data;
    }
    
    void setDataFile(const std::string& fileName) {
        dataFileName_ = fileName;
    }

    void setRegExp(const std::string& regExp) {
        regExp_ = regExp;
    }
    
    std::vector<Token> getTokens();
    bool hasNextToken();
    Token getNextToken();

private:
    char* data_ = nullptr;
    std::string dataFileName_;
    std::string regExp_;
};

#endif
