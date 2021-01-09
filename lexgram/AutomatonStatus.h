#ifndef AUTOMATONSTATUS_H
#define AUTOMATONSTATUS_H

#include <map>
#include <set>

class AutomatonStatus {
public:
    void addTransfer(char ch, AutomatonStatus* transferStatus);
    std::set<AutomatonStatus*> transfer(char ch);
    
private:
    std::map<char, std::set<AutomatonStatus*>> transferTables_;
};

#endif // AUTOMATONSTATUS_H
