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
        
    void addSubRegExpNode(RegExpNode* regExpNode) {
        subRegExpNodes_.push_back(regExpNode);
    }
    
    void setSubRegExpNodes(const std::vector<RegExpNode*>& regExpNodes) {
        subRegExpNodes_ = regExpNodes;
    }
    
    std::vector<RegExpNode*> getSubRegExpNodes() {
        return subRegExpNodes_;
    }
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
