#ifndef FINITEAUTOMATON_H
#define FINITEAUTOMATON_H

#include <vector>
#include <string>

#include "Token.h"

class FiniteAutomaton {
public:
    void setData(char* data) {
        data_ = data;
    }
    
    void setDataFileName(const std::string& dataFileName) {
        dataFileName_ = dataFileName;
    }
    
    std::vector<Token> getTokens();
    bool hasNextToken();
    Token getNextToken();
private:
    char* data_;
    std::string dataFileName_;
};

#endif // FINITEAUTOMATON_H
