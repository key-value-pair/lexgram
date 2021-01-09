#ifndef AUTOMATONSTATUS_H
#define AUTOMATONSTATUS_H

#include <map>
#include <set>

#define epsilon '\0'

class AutomatonStatus {
public:
    bool hasTransfer(char ch) {
        return transferTables_.count(ch) == 1;
    }
    
    void addTransfer(char ch, AutomatonStatus* transferStatus);
    std::set<AutomatonStatus*> transfer(char ch);
    
private:
    std::map<char, std::set<AutomatonStatus*>> transferTables_;
};

#endif // AUTOMATONSTATUS_H
