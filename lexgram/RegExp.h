#ifndef REGEXP_H
#define REGEXP_H

#include <string>

class RegExpNode {
public:
    enum NodeType {
        Normal,
        Star,
        Or
    }
    
    RegExpNode(NodeType nodeType):
        nodeType_(nodeType) {}
    RegExpNode(const std::string& regExpStr):
        regExpStr_(regExpStr) {}
        
private:
    NodeType nodeType_ = Normal;
    std::string regExpStr_;
    std::vector<RegExpNode*> subRegExpNodes_;
};

class RegExp {
public:
    RegExp(const std::string& regExpStr):
        regExpStr_(regExpStr) {}
private:
    std::string regExpStr_;
};
#endif // REGEXP_H
