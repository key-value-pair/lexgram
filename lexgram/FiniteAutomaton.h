#ifndef FINITEAUTOMATON_H
#define FINITEAUTOMATON_H

#include <vector>
#include <string>

#include "Token.h"
#include "AutomatonStatus.h"

class FiniteAutomaton {
public:
    void setData(char* data) {
        data_ = data;
    }
    
    void setDataFileName(const std::string& dataFileName) {
        dataFileName_ = dataFileName;
    }
    
    void setRegExp(const std::string& regExp) {
        regExp_ = regExp;
    }
    
    std::vector<Token> getTokens();
    bool hasNextToken();
    Token getNextToken();
private:
    void _buildAutomatonStatus();
    void _convertNFAtoDFA();
    void _minimizeDFA();
private:
    char* data_ = nullptr;
    std::string dataFileName_;
    std::string regExp_;
    std::vector<AutomatonStatus*> automatonStatus_;
};

#endif // FINITEAUTOMATON_H
